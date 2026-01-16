#include <queue>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Pass/IROptimizer.h"
#include "Pass/DomTreePass.h"
#include "Pass/LiveVariableAnalysis.h" // [必要] 后端寄存器分配依赖此分析
#include "Pass/Mem2RegPass.h"
#include "Pass/OptUtils.h"
#include "Pass/ScalarOpts.h"           // [新增] 标量优化 Pass
#include "Pass/LoopOpts.h"             // [新增] 循环优化 Pass

IROptimizer::IROptimizer(GlobalUnit *gu) {
    this->globalUnit = gu;
}

void IROptimizer::Optimize() {
    // 1. 构建控制流图 (必要基础步骤)
    // 这一步会将各个 BasicBlock 的前驱(pred)和后继(succ)关系建立起来
    BuildCFG();
    
    // 简单的全局变量常量化处理 (保留原有逻辑)
    Constlize(); 

    // 2. [阶段一] 基础标量优化迭代
    // 目标：在做复杂的循环优化前，先尽可能把栈操作(load/store)转为寄存器操作，
    // 并消除显而易见的死代码。这能让循环优化更容易识别出"不变式"。
    ScalarOpts* scalarOpts = new ScalarOpts(this->globalUnit);
    bool changed = true;
    int max_iter = 10; // 限制迭代次数，防止因震荡导致的死循环

    while (changed && max_iter-- > 0) {
        scalarOpts->changed = false;
        
        // 顺序很重要：
        // (1) StoreLoadForwarding: 打通内存数据流 (Stack -> Reg)
        scalarOpts->runStoreLoadForwarding();   
        // (2) ConstantPropagation: 基于寄存器值做计算 (e.g. %1=10, %2=%1+20 -> %2=30)
        scalarOpts->runConstantPropagation();   
        // (3) AlgebraicSimplification: 化简代数恒等式 (e.g. x+0 -> x)
        scalarOpts->runAlgebraicSimplification();
        // (4) CFGSimplification: 移除死分支 (e.g. br i1 true, L1, L2 -> br L1)
        // 注意：这步会改变图结构
        scalarOpts->runCFGSimplification(); 
        // (5) DCE: 删除无用指令和不可达块
        scalarOpts->runDeadCodeElimination();
        
        changed = scalarOpts->changed;
    }

    // 3. [阶段二] 循环优化 (Loop Invariant Code Motion)
    // 前置条件：必须有正确的支配树 (DomTree)。
    // 由于前面的标量优化(特别是 CFGSimplification)可能改变了图结构，
    // 导致旧的支配关系失效，因此必须在这里(重新)构建支配树。
    
    DomTreePass* domTreePass = new DomTreePass(this->globalUnit);
    domTreePass->run(); // 构建支配树

    // 执行循环优化
    LoopOpts* loopOpts = new LoopOpts(this->globalUnit, domTreePass);
    loopOpts->Run();

    // 4. [阶段三] 收尾清理
    // 循环外提可能会把指令提到循环前，导致原位置变为空或者产生了新的常量传播机会。
    // 再跑一遍标量优化可以清理这些残留。
    // (通常跑一次即可，不需要循环迭代)
    if (true) { 
        scalarOpts->changed = false;
        scalarOpts->runStoreLoadForwarding();
        scalarOpts->runConstantPropagation();
        scalarOpts->runCFGSimplification();
        scalarOpts->runDeadCodeElimination();
    }

    // 5. 活跃变量分析 (Live Variable Analysis)
    // 这是为后端寄存器分配 (LinearScan) 做准备的必要步骤。
    // 它会计算每个基本块的 live_in 和 live_out 集合。
    LiveVariableAnalysis* lva = new LiveVariableAnalysis(this->globalUnit);
    lva->analysis();
    
    // 6. 内存清理 (Pass 对象通常用完即弃)
    delete scalarOpts;
    delete domTreePass;
    delete loopOpts;
    // lva 对象如果其分析结果存储在 GlobalUnit/Function 中则可以删除，
    // 如果后端直接使用 lva 对象则不能删。根据原代码习惯暂时保留 lva 指针。
    // delete lva; 
}

void IROptimizer::BuildCFG() {
    // 使用 BFS 遍历可达块，并移除未访问到的死块（不可达块）
    for(auto&[name,func]: globalUnit->func_table){
        if(func->entry == nullptr) continue;

        std::set<BasicBlock*> vis;
        std::queue<BasicBlock*> q;
        q.push(func->entry);
        
        while(!q.empty()){
            BasicBlock * block = q.front(); q.pop();
            if(vis.count(block)) continue;
            vis.insert(block);
            for(auto bb:block->succ){
                q.push(bb);
            }
        }

        auto& v = func->block_list;
        std::vector<BasicBlock *> not_visited;
        for(auto & it : v){
            if(!vis.count(it)){ // not visited
                not_visited.push_back(it);
            }
        }

        for(auto bb:not_visited){
            // 注意：这里调用 DelBlock 需要确保该函数正确处理了前驱后继关系的断开
            // 如果 DelBlock 只是从列表中移除，可能不够彻底，但在 BuildCFG 阶段
            // 我们主要关注的是识别出哪些块是图的一部分。
            DelBlock(bb);
        }
    }
}

void IROptimizer::debug() {
    for(auto&[name,func]:globalUnit->func_table){
        for(auto block: func->block_list){
            for(auto instr: block->local_instr){
                if(!instr->def_list.empty()){
                    ValueRef * def = *(instr->def_list.begin());
                    std::cerr << def->name << " :" << std::endl;
                    for(auto use : def->use){
                        use->outPut(std::cerr);
                    }
                }
            }
        }
    }
}

void IROptimizer::Constlize() {
    for(auto &[name,symbol]: globalUnit->global_symbol_table){
        // 如果全局符号不是数组且没有定义指令（通常意味着它是初始化的全局变量或外部变量）
        // 且代码中只是读取它，尝试替换为常量值
        if(symbol->symbolType->type != ARRAYTYPE && symbol->def.empty()){
            // 复制一份 use 列表进行遍历，防止迭代器失效（虽然这里是替换操作，可能修改 use 链）
            // 原代码直接遍历 symbol->use，如果 replaceAllUsesOf 修改了 symbol->use 可能会有问题
            // 但根据 ValueRef 的实现，use 链通常是被替换者的 use 链。
            // 这里 symbol 是被读取的变量，load 是读取指令。
            
            // 注意：原代码逻辑稍微有点奇怪，通常是对 load 的结果进行替换。
            // 假设 load->def_list[0] 是 load 指令定义的值（即寄存器）。
            // 我们要把所有使用该寄存器的地方，替换成 symbol->constVal。
            
            // 安全性修复：增加判空和拷贝
            std::vector<Instruction*> uses = symbol->use; 
            for(auto load: uses){
                if (!load->def_list.empty()) {
                    ValueRef* val = *(load->def_list.begin());
                    // 只有当 symbol 确实有常量值时才替换
                    if(symbol->constVal) {
                        replaceAllUsesOf(val, symbol->constVal);
                    }
                }
            }
        }
    }
}