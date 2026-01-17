#include <queue>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Pass/IROptimizer.h"
#include "Pass/DomTreePass.h"
#include "Pass/LiveVariableAnalysis.h"
#include "Pass/Mem2RegPass.h"
#include "Pass/OptUtils.h"
#include "Pass/ScalarOpts.h"
#include "Pass/LoopOpts.h"
#include "Pass/PhiElimination.h"

IROptimizer::IROptimizer(GlobalUnit *gu) {
    this->globalUnit = gu;
}

void IROptimizer::Optimize() {
    // ==========================================================
    // 1. 基础设施构建 (Prepare)
    // ==========================================================
    BuildCFG();
    
    // 全局变量常量化 (不依赖 SSA)
    Constlize();

    // ==========================================================
    // 2. 构建 SSA 形式 (Mem2Reg) - 核心重构点
    // ==========================================================
    // 2.1 先构建支配树 (Mem2Reg 计算支配边界需要)
    DomTreePass* domTreePass = new DomTreePass(this->globalUnit);
    domTreePass->run();

    // 2.2 执行 Mem2Reg，消除 alloc/load/store，引入 Phi
    Mem2RegPass* mem2Reg = new Mem2RegPass(this->globalUnit);
    mem2Reg->run();
    delete mem2Reg; // Mem2Reg 是一次性的，跑完就可以删了

    // ==========================================================
    // 3. 标量优化迭代 (Scalar Optimization)
    // ==========================================================
    // 此时代码已处于 SSA 形式，常量传播和 DCE 效率极高
    ScalarOpts* scalarOpts = new ScalarOpts(this->globalUnit);
    bool changed = true;
    int max_iter = 10; 

    while (changed && max_iter-- > 0) {
        scalarOpts->changed = false;
        
        // (1) 常量传播: 现在的 SSA 形式下，%2 = add 1, 2 会直接被折叠
        scalarOpts->runConstantPropagation();   
        
        // (2) 代数化简: x+0 -> x
        scalarOpts->runAlgebraicSimplification();
        
        // (3) StoreLoadForwarding: 
        // 虽然 Mem2Reg 处理了局部变量，但数组和全局变量的 Load/Store 仍需此 Pass 优化
        scalarOpts->runStoreLoadForwarding();   

        // (4) CFG 简化: 移除死分支 (重要: 这会改变 CFG 结构)
        scalarOpts->runCFGSimplification(); 
        
        // (5) 死代码消除
        scalarOpts->runDeadCodeElimination();
        
        changed = scalarOpts->changed;
    }

    // ==========================================================
    // 4. 循环优化 (Loop Optimization)
    // ==========================================================
    // 关键：因为上面的 ScalarOpts (特别是 CFG 简化) 可能改变了图结构，
    // 旧的 DomTree 已经失效，必须重新运行一次！
    domTreePass->run(); 

    // 执行循环优化 (LICM 等)
    // LoopOpts 内部现在使用 DFS 找循环，但外提代码可能仍需支配信息
    LoopOpts* loopOpts = new LoopOpts(this->globalUnit, domTreePass);
    loopOpts->Run();

    // ==========================================================
    // 5. 收尾清理 (Final Cleanup)
    // ==========================================================
    // 循环外提可能引入了新的清理机会
    if (true) { 
        scalarOpts->changed = false;
        scalarOpts->runConstantPropagation();
        scalarOpts->runCFGSimplification();
        scalarOpts->runDeadCodeElimination();
    }
    // 必须在后端生成汇编前，消除 Phi 节点
    PhiElimination* phiElim = new PhiElimination(this->globalUnit);
    phiElim->run();
    // ==========================================================
    // 6. 后端准备 (Backend Preparation)
    // ==========================================================
    // 活跃变量分析，为线性扫描寄存器分配做准备
    LiveVariableAnalysis* lva = new LiveVariableAnalysis(this->globalUnit);
    lva->analysis();
    
    // 资源清理
    delete scalarOpts;
    delete domTreePass; // DomTreePass 对象生命周期结束
    delete loopOpts;
    // delete lva; // 根据你的架构保留或删除
}

void IROptimizer::BuildCFG() {
    // 保持原有的清理不可达块逻辑
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
            if(!vis.count(it)){ 
                not_visited.push_back(it);
            }
        }

        for(auto bb:not_visited){
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
        if(symbol->symbolType->type != ARRAYTYPE && symbol->def.empty()){
            std::vector<Instruction*> uses = symbol->use; 
            for(auto load: uses){
                if (!load->def_list.empty()) {
                    ValueRef* val = *(load->def_list.begin());
                    if(symbol->constVal) {
                        replaceAllUsesOf(val, symbol->constVal);
                    }
                }
            }
        }
    }
}
