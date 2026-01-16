#include "Pass/LoopOpts.h"
#include "IRInstruction.h"
#include "Instruction.h"
#include "BasicBlock.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>

// 空实现的日志函数，编译时会被优化掉
void LoopOpts::debugLog(const std::string& msg) {
    // std::cerr << "[LoopOpts] " << msg << std::endl;
}

// ---------------------------------------------------------
// 核心逻辑：基于 DFS 的强健循环查找 (不依赖 DomTree)
// ---------------------------------------------------------
enum NodeColor { WHITE, GRAY, BLACK };

void LoopOpts::Run() {
    bool anyChange = false;
    
    for (auto& [name, func] : globalUnit->func_table) {
        if (!func || func->block_list.empty()) continue;
        
        // 1. 命名修正 (方便调试 IR)
        int bb_idx = 0;
        for (auto block : func->block_list) {
            if (block->name.empty()) block->name = "BB" + std::to_string(bb_idx++);
        }

        // 2. 查找循环
        auto loops = findLoops(func);
        if (loops.empty()) continue;

        for (auto loop : loops) {
            // 3. 不变式分析
            auto invariants = findInvariants(loop);
            
            if (!invariants.empty()) {
                if (!loop->preHeader) loop->preHeader = createPreHeader(loop, func);
                if (loop->preHeader) {
                    hoistInstructions(loop, invariants, func);
                    this->changed = true;
                    anyChange = true;
                }
            }
            delete loop;
        }
    }
}

// 使用 DFS 寻找回边 (Back Edge: A->B, B is GRAY)
std::vector<Loop*> LoopOpts::findLoops(Function* func) {
    std::vector<Loop*> loops;
    if (!func->entry) return loops;

    std::map<BasicBlock*, NodeColor> color;
    for (auto bb : func->block_list) color[bb] = WHITE;

    // 显式栈模拟递归 DFS
    struct Frame { BasicBlock* u; size_t succIdx; };
    std::vector<Frame> stack;
    stack.push_back({func->entry, 0});
    color[func->entry] = GRAY;

    while (!stack.empty()) {
        Frame& top = stack.back();
        BasicBlock* u = top.u;

        if (top.succIdx < u->succ.size()) {
            BasicBlock* v = u->succ[top.succIdx++];
            
            if (color[v] == GRAY) {
                // 发现回边: u -> v，且 v 正在栈中
                Loop* newLoop = new Loop(v);
                newLoop->blocks.insert(v); // Header
                newLoop->blocks.insert(u); // Latch

                // 反向填充循环体
                std::vector<BasicBlock*> worklist = {u};
                std::set<BasicBlock*> visited = {v, u};

                while (!worklist.empty()) {
                    BasicBlock* curr = worklist.back(); worklist.pop_back();
                    for (auto pred : curr->pred) {
                        if (visited.find(pred) == visited.end()) {
                            visited.insert(pred);
                            newLoop->blocks.insert(pred);
                            worklist.push_back(pred);
                        }
                    }
                }
                loops.push_back(newLoop);
            } 
            else if (color[v] == WHITE) {
                color[v] = GRAY;
                stack.push_back({v, 0});
            }
        } else {
            color[u] = BLACK;
            stack.pop_back();
        }
    }
    return loops;
}

std::set<ValueRef*> LoopOpts::getModifiedPointers(Loop* loop) {
    std::set<ValueRef*> modified;
    for (auto block : loop->blocks) {
        for (auto inst : block->local_instr) {
            if (inst->instType == InstType_Enum::STORE) {
                auto storeInst = static_cast<StoreInstruction*>(inst);
                if (storeInst->dst) modified.insert(storeInst->dst);
            }
        }
    }
    return modified;
}

bool LoopOpts::isDefinedOutside(ValueRef* val, Loop* loop) {
    if (!val) return true;
    if (val->type == RefType::IntConst || val->type == RefType::FloatConst) return true;
    if (val->def.empty()) return true;

    for (auto defInst : val->def) {
        if (defInst->instType == InstType_Enum::ALLOCA) return true;

        IRInstruction* irInst = dynamic_cast<IRInstruction*>(defInst);
        if (irInst && irInst->block && loop->blocks.count(irInst->block)) {
            return false;
        }
    }
    return true;
}

std::vector<Instruction*> LoopOpts::findInvariants(Loop* loop) {
    std::vector<Instruction*> invariants;
    bool foundNew = true;
    std::set<ValueRef*> modifiedPointers = getModifiedPointers(loop);

    while (foundNew) {
        foundNew = false;
        for (auto block : loop->blocks) {
            for (auto inst : block->local_instr) {
                if (inst->deleted) continue;
                if (std::find(invariants.begin(), invariants.end(), inst) != invariants.end()) continue;

                bool canHoist = false;

                // Load
                if (inst->instType == InstType_Enum::LOAD) {
                    auto loadInst = static_cast<LoadInstruction*>(inst);
                    if (loadInst && loadInst->src) {
                        bool mod = modifiedPointers.count(loadInst->src);
                        bool defOut = isDefinedOutside(loadInst->src, loop);
                        if (!mod && defOut) canHoist = true;
                    }
                }
                // Binary
                else if (inst->instType == InstType_Enum::BINARY) {
                    auto bin = static_cast<BinaryInstruction*>(inst);
                    auto isInv = [&](ValueRef* v) {
                        return !v || isDefinedOutside(v, loop) || 
                               (!v->def.empty() && std::find(invariants.begin(), invariants.end(), v->def[0]) != invariants.end());
                    };
                    if (isInv(bin->src1) && isInv(bin->src2)) canHoist = true;
                }

                if (canHoist) {
                    invariants.push_back(inst);
                    foundNew = true;
                }
            }
        }
    }
    return invariants;
}

BasicBlock* LoopOpts::createPreHeader(Loop* loop, Function* func) {
    BasicBlock* header = loop->header;
    std::vector<BasicBlock*> outsidePreds;
    for (auto pred : header->pred) {
        if (loop->blocks.find(pred) == loop->blocks.end()) outsidePreds.push_back(pred);
    }
    if (outsidePreds.empty()) return nullptr;

    static int cnt = 0;
    std::string newLabel = "loop_preheader_" + std::to_string(cnt++);
    BasicBlock* preHeader = new BasicBlock(newLabel, func);
    
    auto it = std::find(func->block_list.begin(), func->block_list.end(), header);
    if (it != func->block_list.end()) func->block_list.insert(it, preHeader);
    else func->block_list.push_back(preHeader);

    preHeader->succ.push_back(header);
    std::vector<BasicBlock*> newHeaderPreds;
    for (auto p : header->pred) {
        if (loop->blocks.find(p) != loop->blocks.end()) newHeaderPreds.push_back(p);
    }
    newHeaderPreds.push_back(preHeader);
    header->pred = newHeaderPreds;
    preHeader->pred = outsidePreds;
    
    for (auto pred : outsidePreds) {
        for (size_t i = 0; i < pred->succ.size(); i++) {
            if (pred->succ[i] == header) pred->succ[i] = preHeader;
        }
        Instruction* term = pred->local_instr.back();
        if (term->instType == InstType_Enum::BR) {
            static_cast<BrInstruction*>(term)->label = preHeader;
        } else if (term->instType == InstType_Enum::CONDBR) {
            auto br = static_cast<CondBrInstruction*>(term);
            if (br->trueLabel == header) br->trueLabel = preHeader;
            if (br->falseLabel == header) br->falseLabel = preHeader;
        }
    }
    preHeader->appendCode(new BrInstruction(header));
    return preHeader;
}

void LoopOpts::hoistInstructions(Loop* loop, const std::vector<Instruction*>& invariants, Function* func) {
    if (!loop->preHeader) return;
    Instruction* branchInst = nullptr;
    if (!loop->preHeader->local_instr.empty()) {
        branchInst = loop->preHeader->local_instr.back();
        loop->preHeader->local_instr.pop_back(); 
    }
    for (auto inst : invariants) {
        IRInstruction* irInst = dynamic_cast<IRInstruction*>(inst);
        if (irInst && irInst->block) {
            auto& blkInsts = irInst->block->local_instr;
            auto it = std::find(blkInsts.begin(), blkInsts.end(), inst);
            if (it != blkInsts.end()) blkInsts.erase(it);
            irInst->block = loop->preHeader; 
        }
        loop->preHeader->local_instr.push_back(inst);
    }
    if (branchInst) loop->preHeader->local_instr.push_back(branchInst);
}