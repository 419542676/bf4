#include "Pass/PhiElimination.h"
#include "IRInstruction.h"
#include "Type.h"
#include "Instruction.h"
#include "ValueRef.h" 
#include <vector>
#include <map>
#include <string>

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
        if(phiResult->type == IntVar || phiResult->type == IntConst) 
            valType = new Type(INT32TYPE);
        else 
            valType = new Type(FLOATTYPE);

        string nameStr = "%phi_demote_" + to_string(Utils::labelCounter++);
        
        // [修正 1]: 构造 Symbol (Alloca 需要指针类型)
        Type* ptrType = new PointerType(valType);
        Symbol* allocaAddr = new Symbol(ptrType, nameStr, false); 
        
        // [关键修正]: 必须将新创建的符号加入到函数的符号表中！
        // 否则 Function::codegen 计算栈偏移量时会漏掉它，导致后端查不到 offset 出现段错误
        func->symbol_table[nameStr] = allocaAddr;

        // [修正 2]: 构造 Alloca 指令
        AllocaInstruction* allocaInst = new AllocaInstruction(allocaAddr, valType, nameStr);
        
        // 插入到 Entry 开头
        auto insertIt = func->entry->local_instr.begin();
        while(insertIt != func->entry->local_instr.end() && (*insertIt)->instType == ALLOCA) {
            insertIt++;
        }
        func->entry->local_instr.insert(insertIt, allocaInst);

        // B. 在所有前驱块的末尾插入 Store
        for (auto const& [predBlock, val] : phi->mp) {
            StoreInstruction* storeInst = new StoreInstruction(allocaAddr, val);
            
            if (predBlock->local_instr.empty()) {
                predBlock->local_instr.push_back(storeInst);
            } else {
                auto it = predBlock->local_instr.end();
                --it; 
                // 如果最后一条是跳转指令，插在它前面
                if ((*it)->instType == BR || (*it)->instType == CONDBR || (*it)->instType == RET) {
                    predBlock->local_instr.insert(it, storeInst);
                } else {
                    predBlock->local_instr.push_back(storeInst);
                }
            }
        }

        // C. 在 Phi 所在块的开头，用 Load 替换 Phi
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

