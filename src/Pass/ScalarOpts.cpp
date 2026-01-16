#include "Pass/ScalarOpts.h"
#include "ValueRef.h"
#include "Instruction.h"
#include "IRInstruction.h"
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm> // 必须包含

// 辅助函数定义
bool isIntConst(ValueRef* v) { return v && v->type == RefType::IntConst; }
int getIntVal(ValueRef* v) { return dynamic_cast<Int_Const*>(v)->value; }
bool isBoolConst(ValueRef* v) { return v && v->type == RefType::BoolConst; }
int getBoolVal(ValueRef* v) { return dynamic_cast<Bool_Const*>(v)->value ? 1 : 0; }
// --- 1. 存储-加载转发 (Load-Store Forwarding) ---
void ScalarOpts::runStoreLoadForwarding() {
    for (auto& [name, func] : globalUnit->func_table) {
        for (auto block : func->block_list) {
            std::map<ValueRef*, ValueRef*> memoryMap;

            for (auto inst : block->local_instr) {
                if (inst->deleted) continue;

                if (inst->instType == InstType_Enum::STORE) {
                    auto storeInst = dynamic_cast<StoreInstruction*>(inst);
                    // 记录：地址(dst) -> 值(src)
                    memoryMap[storeInst->dst] = storeInst->src;
                }
                else if (inst->instType == InstType_Enum::LOAD) {
                    auto loadInst = dynamic_cast<LoadInstruction*>(inst);
                    ValueRef* ptr = loadInst->src; // 源地址
                    ValueRef* dst = loadInst->dst; // 目标寄存器

                    if (memoryMap.count(ptr)) {
                        ValueRef* knownVal = memoryMap[ptr];
                        // 替换所有使用该 Load 结果的地方
                        std::vector<Instruction*> users = dst->use;
                        for (auto user : users) {
                            user->replace(dst, knownVal);
                        }
                        inst->deleted = true;
                        this->changed = true;
                    }
                }
                else if (inst->instType == InstType_Enum::CALL) {
                    memoryMap.clear(); // 函数调用可能修改内存，清空缓存
                }
            }
        }
    }
}

// --- 2. 常量传播与折叠 ---
void ScalarOpts::runConstantPropagation() {
    for (auto& [name, func] : globalUnit->func_table) {
        for (auto block : func->block_list) {
            for (auto inst : block->local_instr) {
                if (inst->deleted) continue;

                // Case A: 二元运算
                if (inst->instType == InstType_Enum::BINARY) {
                    auto binInst = dynamic_cast<BinaryInstruction*>(inst);
                    if (isIntConst(binInst->src1) && isIntConst(binInst->src2)) {
                        ValueRef* newVal = computeBinary(binInst->opTy, binInst->src1, binInst->src2);
                        if (newVal) {
                            std::vector<Instruction*> users = binInst->dst->use;
                            for (auto user : users) user->replace(binInst->dst, newVal);
                            inst->deleted = true;
                            this->changed = true;
                        }
                    }
                }
                // Case B: 比较运算
                else if (inst->instType == InstType_Enum::CMP) {
                    auto cmpInst = dynamic_cast<CmpInstruction*>(inst);
                    if (isIntConst(cmpInst->src1) && isIntConst(cmpInst->src2)) {
                        ValueRef* newVal = computeCmp(cmpInst->opTy, cmpInst->src1, cmpInst->src2);
                        if (newVal) {
                            std::vector<Instruction*> users = cmpInst->result->use;
                            for (auto user : users) user->replace(cmpInst->result, newVal);
                            inst->deleted = true;
                            this->changed = true;
                        }
                    }
                }
                // Case C: 零扩展 (ZExtInstruction)
                else if (inst->instType == InstType_Enum::ZEXT) {
                    auto zextInst = dynamic_cast<ZExtInstruction*>(inst); 
                    if (isIntConst(zextInst->src)) {
                        int val = getIntVal(zextInst->src);
                        ValueRef* newVal = new Int_Const(val);
                        std::vector<Instruction*> users = zextInst->dst->use;
                        for (auto user : users) user->replace(zextInst->dst, newVal);
                        inst->deleted = true;
                        this->changed = true;
                    }
                }
                // Case D: 异或 (Xor) 
                else if (inst->instType == InstType_Enum::XOR) {
                     auto xorInst = dynamic_cast<XorInstruction*>(inst);
                     if (isIntConst(xorInst->src)) {
                        int val = getIntVal(xorInst->src);
                        int res = val ^ 1; // 常量折叠：对值取反
                        ValueRef* newVal = new Int_Const(res);
                        std::vector<Instruction*> users = xorInst->dst->use;
                        for (auto user : users) user->replace(xorInst->dst, newVal);
                        inst->deleted = true;
                        this->changed = true;
                     }
                }
            }
        }
    }
}

// 计算逻辑
ValueRef* ScalarOpts::computeBinary(binaryType op, ValueRef* v1, ValueRef* v2) {
    int val1 = getIntVal(v1);
    int val2 = getIntVal(v2);
    int res = 0;
    if ((op == DIV || op == MOD) && val2 == 0) return nullptr;
    switch (op) {
        case ADD: res = val1 + val2; break;
        case SUB: res = val1 - val2; break;
        case MUL: res = val1 * val2; break;
        case DIV: res = val1 / val2; break;
        case MOD: res = val1 % val2; break;
        case AND: res = (val1 && val2); break;
        case OR:  res = (val1 || val2); break;
        default: return nullptr;
    }
    return new Int_Const(res);
}

ValueRef* ScalarOpts::computeCmp(cmpType op, ValueRef* v1, ValueRef* v2) {
    int val1 = getIntVal(v1);
    int val2 = getIntVal(v2);
    int res = 0;
    switch (op) {
        case EQ: res = (val1 == val2); break;
        case NE: res = (val1 != val2); break;
        case LT: res = (val1 < val2); break;
        case LE: res = (val1 <= val2); break;
        case GT: res = (val1 > val2); break;
        case GE: res = (val1 >= val2); break;
        default: return nullptr;
    }
    return new Int_Const(res);
}

// --- 3. 代数化简 ---
void ScalarOpts::runAlgebraicSimplification() {
    for (auto& [name, func] : globalUnit->func_table) {
        for (auto block : func->block_list) {
            for (auto inst : block->local_instr) {
                if (inst->deleted || inst->instType != InstType_Enum::BINARY) continue;
                auto binInst = dynamic_cast<BinaryInstruction*>(inst);
                ValueRef* replaceVal = nullptr;
                ValueRef* op1 = binInst->src1;
                ValueRef* op2 = binInst->src2;

                if (binInst->opTy == ADD) {
                    if (isIntConst(op2) && getIntVal(op2) == 0) replaceVal = op1;
                    else if (isIntConst(op1) && getIntVal(op1) == 0) replaceVal = op2;
                }
                else if (binInst->opTy == MUL) {
                    if (isIntConst(op2) && getIntVal(op2) == 1) replaceVal = op1;
                    else if (isIntConst(op1) && getIntVal(op1) == 1) replaceVal = op2;
                    else if (isIntConst(op2) && getIntVal(op2) == 0) replaceVal = new Int_Const(0);
                    else if (isIntConst(op1) && getIntVal(op1) == 0) replaceVal = new Int_Const(0);
                }
                if (replaceVal) {
                    std::vector<Instruction*> users = binInst->dst->use;
                    for (auto user : users) user->replace(binInst->dst, replaceVal);
                    inst->deleted = true;
                    this->changed = true;
                }
            }
        }
    }
}

// --- 4. 死代码消除 (增强版：包含指令DCE和块DCE) ---
void ScalarOpts::runDeadCodeElimination() {
    for (auto& [name, func] : globalUnit->func_table) {
        
        // A. 指令级死代码消除
        for (auto block : func->block_list) {
            auto it = block->local_instr.begin();
            while (it != block->local_instr.end()) {
                Instruction* inst = *it;
                if (inst->deleted) {
                    it = block->local_instr.erase(it);
                    this->changed = true;
                    continue;
                }
                
                bool hasSideEffect = (
                    inst->instType == InstType_Enum::STORE || 
                    inst->instType == InstType_Enum::CALL ||
                    inst->instType == InstType_Enum::RET ||
                    inst->instType == InstType_Enum::BR ||
                    inst->instType == InstType_Enum::CONDBR
                );

                if (!hasSideEffect) {
                    bool isUsed = false;
                    for (auto defVal : inst->def_list) {
                        if (!defVal->use.empty()) {
                            isUsed = true;
                            break;
                        }
                    }
                    if (!isUsed) {
                        inst->deleted = true;
                        it = block->local_instr.erase(it);
                        this->changed = true;
                        continue;
                    }
                }
                ++it;
            }
        }

        // B. [关键新增] 基本块级死代码消除
        // 移除那些“无前驱”且“非入口”的基本块
        bool blockChanged = true;
        while(blockChanged) {
            blockChanged = false;
            auto it = func->block_list.begin();
            while (it != func->block_list.end()) {
                BasicBlock* block = *it;
                
                // 如果块没有前驱，并且不是函数的入口块 -> 它是不可达的死块
                if (block->pred.empty() && block != func->entry) {
                    
                    // 1. 维护图连接：通知所有后继，我们要消失了
                    for (auto succ : block->succ) {
                        auto& preds = succ->pred;
                        // 从后继的前驱列表中移除当前块
                        preds.erase(std::remove(preds.begin(), preds.end(), block), preds.end());
                    }
                    
                    // 2. 从函数的基本块列表中真正移除
                    it = func->block_list.erase(it);
                    
                    this->changed = true;
                    blockChanged = true; // 删了一个块，可能导致它的后继也变成死块，需要继续扫描
                } else {
                    ++it;
                }
            }
        }
    }
}
// 5. 控制流简化 (维护 CFG 图连接) ---
void ScalarOpts::runCFGSimplification() {
    for (auto& [name, func] : globalUnit->func_table) {
        for (auto block : func->block_list) {
            if (block->local_instr.empty()) continue;
            Instruction* terminator = block->local_instr.back();

            if (terminator->instType == InstType_Enum::CONDBR) {
                auto condBr = dynamic_cast<CondBrInstruction*>(terminator);
                
                // 统一获取条件值 (支持 IntConst 和 BoolConst)
                bool isConstant = false;
                bool conditionIsTrue = false;

                if (isIntConst(condBr->condition)) {
                    isConstant = true;
                    conditionIsTrue = (getIntVal(condBr->condition) != 0);
                } 
                else if (isBoolConst(condBr->condition)) { // [修复] 增加对 BoolConst 的支持
                    isConstant = true;
                    conditionIsTrue = (getBoolVal(condBr->condition) != 0);
                }

                if (isConstant) {
                    BasicBlock* takenBlock = conditionIsTrue ? condBr->trueLabel : condBr->falseLabel;
                    BasicBlock* notTakenBlock = conditionIsTrue ? condBr->falseLabel : condBr->trueLabel;

                    // 1. 创建新的无条件跳转
                    auto newBr = new BrInstruction(takenBlock);
                    newBr->block = block;
                    
                    // 2. 替换指令
                    block->local_instr.pop_back();
                    block->local_instr.push_back(newBr);
                    terminator->deleted = true;

                    // 3. 维护 CFG 图结构 (关键修复：防止同一目标块被错误断开)
                    // 只有当“走的分支”和“不走的分支”不是同一个块时，才断开与“不走分支”的连接
                    if (takenBlock != notTakenBlock) {
                        // 从当前块的后继中移除 notTakenBlock
                        auto& succs = block->succ;
                        succs.erase(std::remove(succs.begin(), succs.end(), notTakenBlock), succs.end());

                        // 从 notTakenBlock 的前驱中移除当前块
                        auto& preds = notTakenBlock->pred;
                        preds.erase(std::remove(preds.begin(), preds.end(), block), preds.end());
                    }

                    this->changed = true;
                }
            }
        }
    }
}