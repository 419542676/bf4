#ifndef __MACHINE_FUNCTION_H_
#define __MACHINE_FUNCTION_H_

#include "Backend/MachineBlock.hpp"
#include "Backend/MachineInstruction.hpp"
#include "Backend/MachineOperand.hpp"
#include "Function.h"
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <set> // 原代码中使用了 std::set，补全头文件

class MachineUnit;

class MachineFunction {

public:
    MachineUnit *parent;
    std::vector<MachineBlock *> block_list;
    Function *IR_func; // IR级函数
    std::vector<MachineInstruction *> no2inst;
    std::unordered_map<std::string, std::set<std::pair<int, int>>> live_ranges;
    std::unordered_map<std::string, std::set<std::pair<int, int>>> f_live_ranges;
    std::unordered_map<std::string, std::pair<int, int>> live_intervals;
    std::unordered_map<std::string, std::pair<int, int>> f_live_intervals;
    
    // 【修改说明】framesize 记录的是局部变量的大小（原有逻辑）
    int framesize{}; 
    
    // 【新增】用于记录寄存器溢出（Spill）产生的额外栈偏移量
    int current_spill_offset = 0; 

    MachineFunction(MachineUnit *parent_p, Function *func) : parent(parent_p), IR_func(func) {}
    ~MachineFunction() {
        for (auto &block : block_list) {
            delete block;
            block = nullptr;
        }
    }

    void insert_block(MachineBlock *block) {
        block_list.push_back(block);
    }

    void output(std::ostream &os) {
        for (auto block : block_list) {
            block->output(os);
        }
    }

    // 【新增方法】分配溢出槽，修复 LinearScan 中所有变量溢出到同一位置的 bug
    int allocateSpillSlot(int size) {
        // 累加溢出偏移量
        current_spill_offset += size;
        
        // 保持 4 字节对齐 (int/float)
        if (current_spill_offset % 4 != 0) {
            current_spill_offset = (current_spill_offset + 3) / 4 * 4;
        }
        
        // 返回相对帧指针 fp 的偏移量
        // 位置在：原有栈帧大小(framesize) 之下，再往下走 current_spill_offset
        // 这里的 24 是保留给 ra(8字节) + fp(8字节) + 可能的对齐padding，保留原代码的习惯
        // 如果原代码逻辑 framesize 不包含头部，则公式如下：
        return -(framesize + current_spill_offset + 24); 
    }

    // 【新增方法】获取最终的总栈帧大小（原有大小 + 溢出大小）
    // 这个方法应该在生成 Prologue/Epilogue (addi sp, sp, -size) 时调用
    long long getTotalFrameSize() const {
        long long total = framesize + current_spill_offset + 24; // 加上保留区
        // RISC-V 要求栈指针 16 字节对齐
        if (total % 16 != 0) {
            total = (total + 15) / 16 * 16;
        }
        return total;
    }

};

#endif
