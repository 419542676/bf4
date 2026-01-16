#ifndef __MACHINE_BLOCK_H_
#define __MACHINE_BLOCK_H_

#include "Backend/MachineInstruction.hpp"
#include <memory>
#include <ostream>
#include <set>
#include <vector>
#include <list>

class MachineFunction;
class BasicBlock;

class MachineBlock {
public:
    BasicBlock *IRBlock;
    MachineFunction *parent;
    int no;// 基本块编号
    std::vector<MachineBlock *> pred, succ; // 前驱和后继基本块

    std::list<MachineInstruction *> inst_list; // 存储目标机器指令的链表

    std::set<std::string> live_in;
    std::set<std::string> live_out;
    std::set<std::string> f_live_in;
    std::set<std::string> f_live_out;

    std::set<std::string> live_use;
    std::set<std::string> live_def;
    std::set<std::string> f_live_use;
    std::set<std::string> f_live_def;

    int begin_no, end_no;// 基本块内指令的起始和结束编号

    BasicBlock *bb;// 对应的源代码基本块

    MachineBlock(MachineFunction *parent_p, BasicBlock *IR_Block_p) : parent(parent_p), IRBlock(IR_Block_p) {}
    ~MachineBlock() {
        for (auto &inst : inst_list) {
            delete inst;// 释放指令内存
            inst = nullptr;
        }
    }
    
    void insertInst(MachineInstruction *inst) {
        inst->current_it = inst_list.insert(inst_list.end(), inst);
        inst->parent = this;
    }
    
    void output(std::ostream &os) const;
};

#endif