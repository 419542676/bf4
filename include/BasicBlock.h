#include "Type.h"
#include "Backend/MachineBlock.hpp"
#include "ValueRef.h"
#include <set>
#include <vector>
#include <map>
#include <iostream>

#ifndef COMPILER_BASICBLOCK_H
#define COMPILER_BASICBLOCK_H

class Instruction;
class Function;
class DomNode;
class AsmBuilder;
class Loop;

class BasicBlock : public ValueRef{
public:
    std::string label;
    std::vector<BasicBlock *> pred,succ;//前驱和后继块
    std::vector<Instruction*> local_instr;//当前基本块内的指令

    Function * func_belong;//该基本块所属的函数
    DomNode * domNode;//支配树相关

    std::set<ValueRef*> live_in;//存储当前基本块的活跃变量
    std::set<ValueRef*> live_out;

    std::set<ValueRef*> live_use;//存储当前基本块使用的变量
    std::set<ValueRef*> live_def;//存储当前基本块定义的变量

    Loop* belong_loop = nullptr;
    int loop_depth = 0;

    MachineBlock *mBlock;

    BasicBlock(std::string& label,Function * func);

    void appendCode(Instruction* instruction);

    void insertCodeAtFront(Instruction* instruction);

    void Emit(std::ostream &os);

    std::string get_Ref() override { return label; }
    std::string get_TypeName() override { return "label"; }

    void codegen(AsmBuilder *builder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int framesize,
                 vector<Type*> &arguments,
                 bool is_entry = false);
};


#endif
