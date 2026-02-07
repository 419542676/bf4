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
#include "Pass/PeepholeOpts.h" // 新增头文件

IROptimizer::IROptimizer(GlobalUnit *gu) {
    this->globalUnit = gu;
}

void IROptimizer::Optimize() {
    // ==========================================================
    // 1. 基础设施构建 (Prepare)
    // ==========================================================
    BuildCFG();
    Constlize();

    // ==========================================================
    // 2. 构建 SSA 形式 (Mem2Reg)
    // ==========================================================
    DomTreePass* domTreePass = new DomTreePass(this->globalUnit);
    domTreePass->run();

    Mem2RegPass* mem2Reg = new Mem2RegPass(this->globalUnit);
    mem2Reg->run();
    delete mem2Reg;

    // ==========================================================
    // 3. 标量优化迭代 (Scalar Optimization)
    // ==========================================================
    ScalarOpts* scalarOpts = new ScalarOpts(this->globalUnit);
    bool changed = true;
    int max_iter = 10; 

    while (changed && max_iter-- > 0) {
        scalarOpts->changed = false;
        
        scalarOpts->runConstantPropagation();   
        scalarOpts->runAlgebraicSimplification();
        scalarOpts->runStoreLoadForwarding();   
        scalarOpts->runCFGSimplification(); 
        scalarOpts->runDeadCodeElimination();
        
        changed = scalarOpts->changed;
    }

    // ==========================================================
    // 4. 循环优化 (Loop Optimization)
    // ==========================================================
    // 重建 DomTree，因为 CFG 可能已改变
    domTreePass->run(); 

    LoopOpts* loopOpts = new LoopOpts(this->globalUnit, domTreePass);
    loopOpts->Run();

    // ==========================================================
    // 5. 收尾清理 (Final Cleanup)
    // ==========================================================
    if (true) { 
        scalarOpts->changed = false;
        scalarOpts->runConstantPropagation();
        scalarOpts->runCFGSimplification();
        scalarOpts->runDeadCodeElimination();
    }

    // ==========================================================
    // 6. 退出 SSA (Phi Elimination)
    // ==========================================================
    PhiElimination* phiElim = new PhiElimination(this->globalUnit);
    phiElim->run();
    delete phiElim;

    // ==========================================================
    // 7. 窥孔优化 (Peephole Optimization)
    // ==========================================================
    // 专门清理 PhiElimination 产生的冗余 Store-Load
    PeepholeOpts* peephole = new PeepholeOpts(this->globalUnit);
    peephole->run();
    delete peephole;

    // ==========================================================
    // 8. 后端准备 (Backend Preparation)
    // ==========================================================
    LiveVariableAnalysis* lva = new LiveVariableAnalysis(this->globalUnit);
    lva->analysis();
    
    // 资源清理
    delete scalarOpts;
    delete domTreePass;
    delete loopOpts;
    // delete lva; 
}

void IROptimizer::BuildCFG() {
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