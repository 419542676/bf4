#include "Pass/PhiElimination.h"
#include "IRInstruction.h"
#include "Type.h"
#include "Instruction.h"
#include "ValueRef.h"
#include "BasicBlock.h" 
#include "Utils.h"      
#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;

void PhiElimination::run() {
    for (auto &[name, func] : globalUnit->func_table) {
        if (!func->block_list.empty()) {
            runOnFunction(func);
        }
    }
}

void PhiElimination::runOnFunction(Function* func) {
    std::vector<Instruction*> phis;
    // 1. 收集所有 Phi 指令
    for (auto block : func->block_list) {
        for (auto inst : block->local_instr) {
            if (inst->instType == InstType_Enum::PHI) {
                phis.push_back(inst);
            }
        }
    }

    // 2. 逐个处理 Phi
    for (auto inst : phis) {
        auto phi = dynamic_cast<PhiInstruction*>(inst);
        ValueRef* phiResult = phi->result;
        BasicBlock* phiBlock = nullptr;
        
        // 找到 Phi 所在的块
        for(auto bb : func->block_list) {
            for(auto i : bb->local_instr) if(i == phi) { phiBlock = bb; break; }
            if(phiBlock) break;
        }
        if (!phiBlock) continue;

        // A. 在 Entry 块创建临时栈变量
        Type* valType;
        // 确定变量类型
        if(phiResult->type == IntVar || phiResult->type == IntConst || 
           phiResult->type == INT32TYPE || 
           (dynamic_cast<Symbol*>(phiResult) && Type_Enum(dynamic_cast<Symbol*>(phiResult)->symbolType->type) == INT32TYPE)) {
            valType = new Type(INT32TYPE);
        } else {
            valType = new Type(FLOATTYPE);
        }

        string nameStr = "%phi_demote_" + to_string(Utils::labelCounter++);
        
        // [关键修正]：符号类型必须是 valType (如 INT32TYPE)，不能是 PointerType！
        // 这样后端 Load 指令才会生成 LW (-20-offset) 而不是 LD (-24-offset)
        Symbol* allocaAddr = new Symbol(valType, nameStr, false); 
        
        // 加入符号表，让 AsmBuilder 分配栈空间
        func->symbol_table[nameStr] = allocaAddr;

        // 创建 Alloca 指令
        AllocaInstruction* allocaInst = new AllocaInstruction(allocaAddr, valType, nameStr);
        
        // 插入到 Entry 块的开头
        BasicBlock* entryBlock = func->block_list[0]; 
        auto insertIt = entryBlock->local_instr.begin();
        while(insertIt != entryBlock->local_instr.end() && (*insertIt)->instType == InstType_Enum::ALLOCA) {
            insertIt++;
        }
        entryBlock->local_instr.insert(insertIt, allocaInst);

        // B. 在所有前驱块的末尾插入 Store 指令
        for (auto const& [predBlock, val] : phi->mp) {
           StoreInstruction* storeInst = new StoreInstruction(allocaAddr, val);
           
            
            if (predBlock->local_instr.empty()) {
                predBlock->local_instr.push_back(storeInst);
            } else {
                auto it = predBlock->local_instr.end();
                --it; 
                // 插在跳转指令之前
                if ((*it)->instType == InstType_Enum::BR || 
                    (*it)->instType == InstType_Enum::CONDBR || 
                    (*it)->instType == InstType_Enum::RET) {
                    predBlock->local_instr.insert(it, storeInst);
                } else {
                    predBlock->local_instr.push_back(storeInst);
                }
            }
        }

        // C. 在 Phi 所在块的开头，用 Load 替换 Phi 指令
        LoadInstruction* loadInst = new LoadInstruction(phiResult, allocaAddr);
        
        auto& instrs = phiBlock->local_instr;
        for (auto it = instrs.begin(); it != instrs.end(); ++it) {
            if (*it == phi) {
                *it = loadInst; 
                break;
            }
        }
    }
}
