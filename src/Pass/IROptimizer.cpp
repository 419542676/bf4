#include <queue>
#include "Pass/IROptimizer.h"
#include "Pass/DomTreePass.h"
#include "Pass/LiveVariableAnalysis.h" // [关键修复] 必须包含这个头文件
#include "Pass/Mem2RegPass.h"
#include "Pass/OptUtils.h"
#include "Pass/ScalarOpts.h"           // [新增] 包含我们新写的标量优化头文件

IROptimizer::IROptimizer(GlobalUnit *gu) {
    this->globalUnit = gu;
}

void IROptimizer::Optimize() {
    // 1. 构建控制流图 (必要步骤)
    BuildCFG();
    Constlize(); // 保留原有的简单常量处理

    // 2. [移除/注释] 原来的 SSA 构建过程，因为实现不完整会导致错误
    // DomTreePass* domTreePass = new DomTreePass(this->globalUnit);
    // domTreePass->run();
    // Mem2RegPass* mem2reg = new Mem2RegPass(this->globalUnit);
    // mem2reg->run();

    // 3. [新增] 标量优化循环
    // 使用简单的 while 循环进行多次迭代优化
    ScalarOpts* scalarOpts = new ScalarOpts(this->globalUnit);
    bool changed = true;
    int max_iter = 10; // 限制迭代次数，防止死循环

while (changed && max_iter-- > 0) {
        scalarOpts->changed = false;
        
        scalarOpts->runStoreLoadForwarding();   // [关键第一步] 先把 Load 替换成常数
        scalarOpts->runConstantPropagation();   // 然后 10+20 才能变成 30
        scalarOpts->runAlgebraicSimplification();
        scalarOpts->runCFGSimplification();
        scalarOpts->runDeadCodeElimination();
        
        changed = scalarOpts->changed;
    }
    // 4. 活跃变量分析 (为后端寄存器分配做准备)
    // 这里使用了 LiveVariableAnalysis 类，所以必须包含它的头文件
    LiveVariableAnalysis* lva = new LiveVariableAnalysis(this->globalUnit);
    lva->analysis();
}

void IROptimizer::BuildCFG() {
    // 1.bfs && remove unvisited blocks
    for(auto&[name,func]: globalUnit->func_table){
        if(func->entry == nullptr) continue;

        set<BasicBlock*> vis;
        queue<BasicBlock*> q;
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
        vector<BasicBlock *> not_visited;
        for(auto & it : v){
            if(!vis.count(it)){ // not visited
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
                    cerr << def->name << " :" << endl;
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
            for(auto load: symbol->use){
                // 增加空指针检查，防止段错误
                if (!load->def_list.empty()) {
                    ValueRef* val = *(load->def_list.begin());
                    replaceAllUsesOf(val,symbol->constVal);
                }
            }
        }
    }
}
