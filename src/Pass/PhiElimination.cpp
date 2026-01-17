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
        // 简单的类型判断
        if(phiResult->type == INT32TYPE || phiResult->type == IntVar) 
            valType = new Type(INT32TYPE);
        else 
            valType = new Type(FLOATTYPE);

        // [修正 1]: 尝试最常见的 Symbol 构造函数 (名字, 是否全局)
        string nameStr = "%phi_demote_" + to_string(Utils::labelCounter++);
        Symbol* allocaAddr = new Symbol(nameStr, false); // false 表示局部变量
        
        // [修正 2]: 手动设置符号的数据类型为指针 (因为 Alloca 分配的是地址)
        // 注意：allocaAddr->type 是 RefType (SYMBOL)，不需要改
        // 我们要改的是 symbolType
        allocaAddr->symbolType = new PointerType(valType);

        // [修正 3]: 交换 Alloca 参数顺序 (先类型，后目标)
        AllocaInstruction* allocaInst = new AllocaInstruction(valType, allocaAddr);
        
        // 插入到 Entry 开头
        auto insertIt = func->entry->local_instr.begin();
        while(insertIt != func->entry->local_instr.end() && (*insertIt)->instType == ALLOCA) {
            insertIt++;
        }
        func->entry->local_instr.insert(insertIt, allocaInst);

        // B. 在所有前驱块的末尾插入 Store
        for (auto const& [predBlock, val] : phi->mp) {
            // StoreInstruction(值, 地址)
            StoreInstruction* storeInst = new StoreInstruction(val, allocaAddr);
            
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
        // LoadInstruction(地址, 目标寄存器)
        LoadInstruction* loadInst = new LoadInstruction(allocaAddr, phiResult);
        
        auto& instrs = phiBlock->local_instr;
        for (auto it = instrs.begin(); it != instrs.end(); ++it) {
            if (*it == phi) {
                *it = loadInst; 
                break;
            }
        }
    }
}
