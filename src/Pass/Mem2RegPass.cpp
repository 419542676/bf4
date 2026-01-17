#include "Pass/Mem2RegPass.h"
#include "IRInstruction.h"
#include "Pass/OptUtils.h"
#include "Pass/DomNode.h"
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

// 静态全局变量，避免跨文件链接错误
static map<ValueRef*, set<BasicBlock*>> defsites;
static map<BasicBlock*, set<ValueRef*>> placed;
static map<ValueRef*, stack<ValueRef*>> st;
static Undef* undef_val = nullptr; // 用于表示未定义的值

// 辅助函数：清理 Load/Store 的 Use 关系
static void DelUseinLS(ValueRef* ref){
    if (!ref) return;
    for(auto it = ref->use.begin(); it != ref->use.end();){
        if((*it)->instType == LOAD || (*it)->instType == STORE){
            it = ref->use.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Mem2RegPass::run() {
    if (undef_val == nullptr) undef_val = new Undef();

    for(auto& [name,func] : globalUnit->func_table){
        if(func->block_list.empty()) continue;

        // 只有计算了支配树根节点，才能运行 Mem2Reg
        if(func->dom_root != nullptr) {
            st.clear();
            defsites.clear();
            placed.clear();
            
            insertPhi(func);
            renamePhi(func->dom_root);
            mergeEntry(func);
        }
    }
}

void Mem2RegPass::insertPhi(Function *func) {
    // 1. 计算 defsites (变量在哪些块中被定义/Store)
    for(auto block : func->block_list){
        for(auto instr : block->local_instr){
            if(instr->def_list.empty()) continue;
            ValueRef * var = *(instr->def_list.begin());
            // 只处理非全局的 Symbol (局部变量)
            if(var->type == SYMBOL && !dynamic_cast<Symbol*>(var)->is_global)
                defsites[var].insert(block);
        }
    }

    // 2. 插入 Phi 节点 (基于支配边界)
    for(auto& [var, defs]: defsites){
        bool is_int = ((Symbol*)var)->symbolType->type == INT32TYPE;
        
        // Worklist 算法
        vector<BasicBlock*> W(defs.begin(), defs.end());
        
        while(!W.empty()){
            BasicBlock* block = W.back();
            W.pop_back();
            
            if (!block->domNode) continue;

            auto& DF = block->domNode->DF;
            for(auto df_node : DF){
                BasicBlock* bb = df_node->bb;
                if(!placed[bb].count(var)){
                    ValueRef* result;
                    if(is_int)
                        result = new Int_Var("%phi_");
                    else
                        result = new Float_Var("%phi_");

                    // 创建 Phi 指令
                    PhiInstruction * phi = new PhiInstruction(var, result, bb->pred.size());
                    
                    // [重要] 注册 def，防止 LICM 误判为不变量
                    result->def.push_back(phi);

                    Insert_instr_atFront(phi, bb);
                    placed[bb].insert(var);

                    if(defsites[var].find(bb) == defsites[var].end()){
                        defsites[var].insert(bb); // Phi 本身也是定义
                        W.push_back(bb);
                    }
                }
            }
        }
    }
}

void Mem2RegPass::renamePhi(DomNode * root) {
    map<ValueRef*, int> counter;
    BasicBlock* nowBlock = root->bb;
    auto& instructions = nowBlock->local_instr;

    for(auto it = instructions.begin(); it != instructions.end();){
        if((*it)->instType == LOAD){
            LoadInstruction* loadInst = (LoadInstruction*)(*it);
            ValueRef* src = loadInst->src;
            ValueRef* dst = loadInst->dst;

            // 忽略指针类型和全局变量
            if(src->type == Ptr || (src->type == SYMBOL && dynamic_cast<Symbol*>(src)->is_global)) {
                ++it;
                continue;
            }

            // 替换为栈顶值 (最近的定义)
            ValueRef* replaced = nullptr;
            if (st.count(src) && !st[src].empty()) {
                replaced = st[src].top();
            } else {
                replaced = undef_val;
            }
            
            replaceAllUsesOf(dst, replaced);
            it = instructions.erase(it); // 删除 Load
        }
        else if((*it)->instType == STORE) {
            StoreInstruction* storeInst = (StoreInstruction*)(*it);
            ValueRef* src = storeInst->src;
            ValueRef* dst = storeInst->dst;

            if(dst->type == Ptr || (dst->type == SYMBOL && dynamic_cast<Symbol*>(dst)->is_global)) {
                ++it;
                continue;
            }
            
            st[dst].push(src);
            counter[dst]++;
            DelUseinLS(src); 
            
            it = instructions.erase(it); // 删除 Store
        }
        else if((*it)->instType == PHI){
            PhiInstruction* phi = (PhiInstruction*)(*it);
            ValueRef* var = phi->symbol;
            ValueRef* value = phi->result;
            
            st[var].push(value);
            counter[var]++;
            ++it;
        }
        else{
            ++it;
        }
    }

    // 填充后继块的 Phi 参数
    for(auto next: nowBlock->succ){
        for(auto instr: next->local_instr){
            if(instr->instType != PHI) break;
            auto phi = (PhiInstruction*)instr;
            ValueRef* var = phi->symbol;
            
            ValueRef* val = nullptr;
            if(st[var].empty()){
                val = undef_val;
            } else {
                val = st[var].top();
            }
            
            // 使用 addIncoming (需要在 IRInstruction.h 中有此方法，或者直接操作 mp 和 use)
            phi->addIncoming(val, nowBlock);
        }
    }

    // [修正] 这里改为 children，与 DomNode.h 保持一致
    for(auto child: root->children){
        renamePhi(child);
    }

    // 恢复栈状态 (Backtracking)
    for(auto&[var,cnt]:counter){
        for(int i=0;i<cnt;++i)
            st[var].pop();
    }
}

void Mem2RegPass::mergeEntry(Function *func) {
    if (!func->entry || func->entry->succ.empty()) return;

    BasicBlock* entry = func->entry;
    BasicBlock* next = entry->succ[0];

    // 将 entry 块中的数组 alloca 移动到 next 块
    auto& v = entry->local_instr;
    stack<Instruction*> stk;
    
    for(auto it = v.begin(); it != v.end();){
        if ((*it)->instType == ALLOCA) {
            auto instr = dynamic_cast<AllocaInstruction*>(*it);
            if(instr->varType->type == ARRAYTYPE) {
                stk.push(*it);
            }
        }
        it = v.erase(it);
    }

    while(!stk.empty()){
        Insert_instr_atFront(stk.top(), next);
        stk.pop();
    }

    // 移除 entry 块
    next->pred.clear();
    if (!func->block_list.empty() && func->block_list[0] == entry) {
        func->block_list.erase(func->block_list.begin());
    }
    func->entry = next;
}
