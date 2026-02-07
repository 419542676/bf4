#include "Function.h"
#include "IRInstruction.h"
#include "Type.h"
#include "Backend/MachineFunction.hpp"
#include "Backend/AsmBuilder.hpp" 
#include <queue>
#include <iostream>
#include <set>

Function::Function(string name, FuncType *funcType) {
    this->name = std::move(name);
    this->funcType = funcType;
    this->dom_root = nullptr;
    this->entry = nullptr;
}

void Function::appendBlock(BasicBlock *block) {
    this->block_list.push_back(block);
}


void Function::Emit(std::ostream &os) {
    os << this->debugInfo;
    for(BasicBlock *block : block_list){
        block -> Emit(os);
    }
    if (this->debugInfo.length() != 0) os << "}" << endl;
}

void Function::PrintSymbol() {
    cout << this->name << " Symbols:" << endl;
    for(const auto& it:symbol_table){
        cout << it.first << ": " << it.second->symbolType->getSize() << endl;
    }
}

void Function::codegen(AsmBuilder *builder) {
        std::cerr << "  [F-DEBUG] Function::codegen start: " << this->name << std::endl;
        
        auto cur_unit = builder->getUnit();
        // 如果这里崩溃，可能是 MachineFunction 构造函数与头文件不匹配
        auto cur_func = new MachineFunction(cur_unit, this); 
        builder->setFunction(cur_func);

        int offset = 0;
        std::map<std::string, int> offset_table;
        std::map<std::string, int> size_table;
        
        std::cerr << "  [F-DEBUG] Processing symbol table (" << symbol_table.size() << " entries)" << std::endl;
        for (auto &[sym_name, sym] : symbol_table) {
            // [Check 1] 检查指针有效性
            if (!sym) {
                std::cerr << "  [CRITICAL ERROR] Symbol '" << sym_name << "' is NULL!" << std::endl;
                exit(1);
            }
            // [Check 2] 检查 Type 有效性
            if (!sym->symbolType) {
                std::cerr << "  [CRITICAL ERROR] Symbol '" << sym_name << "' has NULL type!" << std::endl;
                exit(1);
            }
            
            // std::cerr << "    [Sym] " << sym_name << std::endl; // 调试详细信息
            offset_table[sym_name] = offset;
            int size = sym->symbolType->getSize();
            size_table[sym_name] = size;
            offset += size;
        }
        
        std::cerr << "  [F-DEBUG] Framesize: " << (offset + 16) << std::endl;
        cur_func->framesize = offset + 16;

        std::cerr << "  [F-DEBUG] Processing " << block_list.size() << " blocks" << std::endl;
        for(int i=0;i<block_list.size();i++){
           BasicBlock* bb = block_list[i];
           if(!bb) {
               std::cerr << "  [CRITICAL ERROR] Block " << i << " is NULL!" << std::endl;
               continue;
           }
           std::cerr << "    [B-DEBUG] Block " << i << " codegen start" << std::endl;
           
           // 注意：这里我们移除了 BasicBlock::codegen 里的打印，如果崩在这里，说明是某条指令的 codegen 挂了
           bb->codegen(builder, offset_table, size_table, offset + 16, this->funcType->arguments, i == 0);
           
           std::cerr << "    [B-DEBUG] Block " << i << " codegen done" << std::endl;
        }
        
        std::cerr << "  [F-DEBUG] Function::codegen finishing" << std::endl;
        cur_unit->insert_func(cur_func);
}

static void dfs(BasicBlock *cur, std::vector<BasicBlock *> &result, std::set<BasicBlock *> &visited) {
    visited.insert(cur);
    for (auto bb : cur->succ)
        if (visited.find(bb) == visited.end()) dfs(bb, result, visited);
    result.push_back(cur);
}

std::vector<BasicBlock *> Function::getReversePostOrder() {
    std::vector<BasicBlock *> result{};
    std::set<BasicBlock *> visited{};
    if (block_list.empty()) return result; 
    dfs(block_list[0], result, visited);
    return std::vector<BasicBlock *>(result.rbegin(), result.rend());
}
