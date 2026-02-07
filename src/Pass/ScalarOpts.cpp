#include "Pass/ScalarOpts.h"
#include "ValueRef.h"      // 包含 Int_Const 等定义
#include "IRInstruction.h" // 包含 BinaryInstruction 等定义
#include <iostream>
#include <vector>
#include <algorithm> // for std::remove

// =========================================================
// 1. 适配层：根据 ValueRef.h 定制的辅助函数
// =========================================================

// 判断是否为整数常量，并获取值
static bool getIntValue(ValueRef* val, int& value) {
    if (!val) return false;
    
    // 使用 dynamic_cast 转换为 Int_Const 子类
    if (auto c = dynamic_cast<Int_Const*>(val)) {
        value = c->value; // 访问 Int_Const 的 value 成员
        return true;
    }
    return false;
}

// 创建一个新的整数常量
static ValueRef* createIntConst(int value) {
    // 调用 Int_Const 的构造函数
    return new Int_Const(value);
}

// =========================================================
// 2. 核心逻辑实现
// =========================================================

bool ScalarOpts::hasSideEffects(Instruction* inst) {
    // Store, Call, Ret, Br, CondBr 都有副作用或控制流作用，不能直接删
    if (inst->instType == InstType_Enum::STORE) return true;
    if (inst->instType == InstType_Enum::CALL) return true;
    if (inst->instType == InstType_Enum::RET) return true;
    if (inst->instType == InstType_Enum::BR) return true;
    if (inst->instType == InstType_Enum::CONDBR) return true;
    return false;
}

// 从操作数的 use 链中移除当前指令 (用于 DCE)
void ScalarOpts::removeUseFromOperands(Instruction* inst) {
    auto removeFromList = [&](ValueRef* val) {
        if (!val) return;
        auto& uses = val->use;
        // 使用 erase-remove idiom 删除指定的 inst
        uses.erase(std::remove(uses.begin(), uses.end(), inst), uses.end());
    };

    // 1. 二元运算
    if (auto bin = dynamic_cast<BinaryInstruction*>(inst)) {
        removeFromList(bin->src1);
        removeFromList(bin->src2);
    }
    // 2. 比较运算
    else if (auto cmp = dynamic_cast<CmpInstruction*>(inst)) {
        removeFromList(cmp->src1);
        removeFromList(cmp->src2);
    }
    // 3. Load
    else if (auto load = dynamic_cast<LoadInstruction*>(inst)) {
        removeFromList(load->src);
    }
    // 4. 其他指令 (如有 Zext, Bitcast 等根据需要添加)
}

int ScalarOpts::computeInt(binaryType op, int v1, int v2) {
    switch (op) {
        case ADD: return v1 + v2;
        case SUB: return v1 - v2;
        case MUL: return v1 * v2;
        case DIV: return (v2 != 0) ? (v1 / v2) : 0; 
        case MOD: return (v2 != 0) ? (v1 % v2) : 0;
        case AND: return v1 & v2;
        case OR:  return v1 | v2;
        default: return 0;
    }
}

int ScalarOpts::computeCmp(cmpType op, int v1, int v2) {
    switch (op) {
        case EQ: return v1 == v2;
        case NE: return v1 != v2;
        case GT: return v1 > v2;
        case GE: return v1 >= v2;
        case LT: return v1 < v2;
        case LE: return v1 <= v2;
        default: return 0;
    }
}

// =========================================================
// 3. 常量传播 Pass
// =========================================================
void ScalarOpts::runConstantPropagation() {
    for (auto& [name, func] : globalUnit->func_table) {
        for (auto bb : func->block_list) {
            for (auto it = bb->local_instr.begin(); it != bb->local_instr.end(); ) {
                Instruction* inst = *it;
                bool replaced = false;

                // --- 二元运算 ---
                if (auto bin = dynamic_cast<BinaryInstruction*>(inst)) {
                    int v1, v2;
                    if (getIntValue(bin->src1, v1) && getIntValue(bin->src2, v2)) {
                        // [修改] 使用 bin->opTy
                        int res = computeInt(bin->opTy, v1, v2);
                        ValueRef* newConst = createIntConst(res);
                        
                        if (!inst->def_list.empty()) {
                            ValueRef* defVal = *inst->def_list.begin();
                            std::vector<Instruction*> users = defVal->use; 
                            for(auto user : users) {
                                user->replace(defVal, newConst);
                            }
                        }
                        
                        removeUseFromOperands(inst);
                        it = bb->local_instr.erase(it);
                        replaced = true;
                        changed = true;
                    }
                }
                // --- 比较运算 ---
                else if (auto cmp = dynamic_cast<CmpInstruction*>(inst)) {
                    int v1, v2;
                    if (getIntValue(cmp->src1, v1) && getIntValue(cmp->src2, v2)) {
                        // [修改] 使用 cmp->opTy
                        int res = computeCmp(cmp->opTy, v1, v2);
                        ValueRef* newConst = createIntConst(res); // 1 或 0
                        
                        if (!inst->def_list.empty()) {
                            ValueRef* defVal = *inst->def_list.begin();
                            std::vector<Instruction*> users = defVal->use;
                            for(auto user : users) user->replace(defVal, newConst);
                        }
                        
                        removeUseFromOperands(inst);
                        it = bb->local_instr.erase(it);
                        replaced = true;
                        changed = true;
                    }
                }

                if (!replaced) {
                    ++it;
                }
            }
        }
    }
}

// =========================================================
// 4. 代数化简 Pass
// =========================================================
void ScalarOpts::runAlgebraicSimplification() {
    for (auto& [name, func] : globalUnit->func_table) {
        for (auto bb : func->block_list) {
            for (auto it = bb->local_instr.begin(); it != bb->local_instr.end(); ) {
                Instruction* inst = *it;
                bool simplified = false;

                if (auto bin = dynamic_cast<BinaryInstruction*>(inst)) {
                    ValueRef* src1 = bin->src1;
                    ValueRef* src2 = bin->src2;
                    int v1 = 0, v2 = 0;
                    bool isC1 = getIntValue(src1, v1);
                    bool isC2 = getIntValue(src2, v2);
                    
                    ValueRef* defVal = inst->def_list.empty() ? nullptr : *inst->def_list.begin();

                    if (defVal) {
                        // [修改] 使用 bin->opTy
                        
                        // 规则 1: x + 0 = x
                        if (bin->opTy == ADD) {
                            if (isC2 && v2 == 0) {
                                std::vector<Instruction*> users = defVal->use;
                                for(auto user : users) user->replace(defVal, src1);
                                simplified = true;
                            } else if (isC1 && v1 == 0) {
                                std::vector<Instruction*> users = defVal->use;
                                for(auto user : users) user->replace(defVal, src2);
                                simplified = true;
                            }
                        }
                        // 规则 2: x - 0 = x
                        else if (bin->opTy == SUB) {
                            if (isC2 && v2 == 0) {
                                std::vector<Instruction*> users = defVal->use;
                                for(auto user : users) user->replace(defVal, src1);
                                simplified = true;
                            }
                            // 规则 3: x - x = 0
                            else if (src1 == src2) {
                                ValueRef* zero = createIntConst(0);
                                std::vector<Instruction*> users = defVal->use;
                                for(auto user : users) user->replace(defVal, zero);
                                simplified = true;
                            }
                        }
                        // 规则 4: x * 1 = x; x * 0 = 0
                        else if (bin->opTy == MUL) {
                            if (isC2) {
                                if (v2 == 1) { // x * 1 = x
                                    std::vector<Instruction*> users = defVal->use;
                                    for(auto user : users) user->replace(defVal, src1);
                                    simplified = true;
                                } else if (v2 == 0) { // x * 0 = 0
                                    ValueRef* zero = createIntConst(0);
                                    std::vector<Instruction*> users = defVal->use;
                                    for(auto user : users) user->replace(defVal, zero);
                                    simplified = true;
                                }
                            }
                             else if (isC1) { 
                                if (v1 == 1) { // 1 * x = x
                                    std::vector<Instruction*> users = defVal->use;
                                    for(auto user : users) user->replace(defVal, src2);
                                    simplified = true;
                                } else if (v1 == 0) { // 0 * x = 0
                                    ValueRef* zero = createIntConst(0);
                                    std::vector<Instruction*> users = defVal->use;
                                    for(auto user : users) user->replace(defVal, zero);
                                    simplified = true;
                                }
                            }
                        }
                    }
                }

                if (simplified) {
                    removeUseFromOperands(inst);
                    it = bb->local_instr.erase(it);
                    changed = true;
                } else {
                    ++it;
                }
            }
        }
    }
}

// =========================================================
// 5. 死代码消除 Pass
// =========================================================
void ScalarOpts::runDeadCodeElimination() {
    bool localChanged = true;
    while (localChanged) {
        localChanged = false;
        
        for (auto& [name, func] : globalUnit->func_table) {
            for (auto bb : func->block_list) {
                for (auto it = bb->local_instr.begin(); it != bb->local_instr.end(); ) {
                    Instruction* inst = *it;
                    
                    if (!hasSideEffects(inst)) {
                        bool used = false;
                        if (!inst->def_list.empty()) {
                            ValueRef* def = *inst->def_list.begin();
                            if (!def->use.empty()) {
                                used = true;
                            }
                        }
                        
                        if (!used) {
                            removeUseFromOperands(inst);
                            it = bb->local_instr.erase(it);
                            localChanged = true;
                            changed = true;
                            continue;
                        }
                    }
                    ++it;
                }
            }
        }
    }
}

void ScalarOpts::runStoreLoadForwarding() {}
void ScalarOpts::runCFGSimplification() {}
