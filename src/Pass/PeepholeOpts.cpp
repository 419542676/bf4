#include "Pass/PeepholeOpts.h"
#include "IRInstruction.h"
#include "Instruction.h"
#include "BasicBlock.h"
#include <iostream>
#include <vector>

// 辅助函数：手动替换指令中的源操作数 (Use)，坚决不碰 dst (Def)
static void safeReplaceUse(Instruction* inst, ValueRef* oldVal, ValueRef* newVal) {
    // 1. 二元运算 (add, sub, mul...)
    if (auto bin = dynamic_cast<BinaryInstruction*>(inst)) {
        if (bin->src1 == oldVal) bin->src1 = newVal;
        if (bin->src2 == oldVal) bin->src2 = newVal;
    }
    // 2. 比较运算 (icmp...)
    else if (auto cmp = dynamic_cast<CmpInstruction*>(inst)) {
        if (cmp->src1 == oldVal) cmp->src1 = newVal;
        if (cmp->src2 == oldVal) cmp->src2 = newVal;
    }
    // 3. 存储 (Store) - 只替换 src (要存的值)
    else if (auto store = dynamic_cast<StoreInstruction*>(inst)) {
        if (store->src == oldVal) store->src = newVal;
    }
    // 4. 加载 (Load) - 只替换 src (地址)
    else if (auto load = dynamic_cast<LoadInstruction*>(inst)) {
        if (load->src == oldVal) load->src = newVal;
    }
    // 5. 分支 (CondBr)
    else if (auto br = dynamic_cast<CondBrInstruction*>(inst)) {
        // 【注意】如果这里报错 "no member condition"，请去 include/IRInstruction.h 
        // 查看 CondBrInstruction 里的条件变量叫什么名字 (可能是 src, cond, cond_, 等等)
        // 然后修改下面这行：
        // if (br->cond == oldVal) br->cond = newVal; // 原代码
        // 猜测你的成员变量名可能是 condition ?
         if (br->condition == oldVal) br->condition = newVal;
    }
    // 6. 函数调用 (Call)
    else if (auto call = dynamic_cast<CallInstruction*>(inst)) {
        for (size_t i = 0; i < call->args.size(); ++i) {
            if (call->args[i] == oldVal) call->args[i] = newVal;
        }
    }
    // 7. 返回 (Ret)
    else if (auto ret = dynamic_cast<RetInstruction*>(inst)) {
        if (ret->retVal == oldVal) ret->retVal = newVal;
    }
    
    // 8. [已移除] GetElementPtrInstruction 
    // 你的编译器似乎没有定义这个类，所以这里不需要处理。
    /*
    else if (auto gep = dynamic_cast<GetElementPtrInstruction*>(inst)) {
        if (gep->ptr == oldVal) gep->ptr = newVal;
        for (size_t i = 0; i < gep->dims.size(); ++i) {
            if (gep->dims[i] == oldVal) gep->dims[i] = newVal;
        }
    }
    */
}

void PeepholeOpts::run() {
    bool changed = true;
    int round = 0;
    while (changed && round < 5) {
        changed = false;
        for (auto& [name, func] : globalUnit->func_table) {
            if (func->block_list.empty()) continue;
            changed |= runOnFunction(func);
        }
        round++;
    }
}

void PeepholeOpts::replaceAllUses(Function* func, ValueRef* oldVal, ValueRef* newVal, Instruction* exceptInst) {
    for (auto block : func->block_list) {
        for (auto inst : block->local_instr) {
            // 跳过定义指令
            if (inst == exceptInst) continue;
            
            // 使用安全替换
            safeReplaceUse(inst, oldVal, newVal);
        }
    }
}

bool PeepholeOpts::runOnFunction(Function* func) {
    bool changed = false;

    for (auto bb : func->block_list) {
        // 使用 pred (根据你之前的反馈，成员名是 pred)
        if (bb->pred.size() != 1) continue;

        BasicBlock* predBlock = bb->pred[0];

        for (auto it = bb->local_instr.begin(); it != bb->local_instr.end(); ) {
            Instruction* inst = *it;
            
            if (auto loadInst = dynamic_cast<LoadInstruction*>(inst)) {
                ValueRef* loadAddr = loadInst->src; 
                ValueRef* loadVal  = loadInst->dst; 

                Instruction* matchStore = nullptr;
                if (!predBlock->local_instr.empty()) {
                    for (auto pit = predBlock->local_instr.rbegin(); pit != predBlock->local_instr.rend(); ++pit) {
                        Instruction* pInst = *pit;
                        
                        if (auto storeInst = dynamic_cast<StoreInstruction*>(pInst)) {
                            // 检查地址一致性
                            if (storeInst->dst == loadAddr) {
                                matchStore = pInst;
                                break; 
                            }
                        }
                        
                        // 遇到 Call 停止，防止副作用
                        if (pInst->instType == InstType_Enum::CALL) {
                            break;
                        }
                    }
                }

                if (matchStore) {
                    auto storeInst = dynamic_cast<StoreInstruction*>(matchStore);
                    ValueRef* storeVal = storeInst->src; 

                    // 执行替换 (排除 Load 本身)
                    replaceAllUses(func, loadVal, storeVal, inst);

                    // 删除 Load
                    it = bb->local_instr.erase(it);
                    changed = true;
                    continue; 
                }
            }
            ++it;
        }
    }
    return changed;
}