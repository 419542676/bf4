#include "Function.h"
#include "Backend/AsmBuilder.hpp"
#include "Backend/MachineFunction.hpp"
#include <memory>
#include "Instruction.h"
#include <vector>
#include <map>

#ifndef COMPILER_GLOBALUNIT_H
#define COMPILER_GLOBALUNIT_H


class GlobalUnit {
public:
    map<string,Function*> func_table;
    //全局符号表
    map<string,Symbol*> global_symbol_table;
    vector<Instruction*> global_instr;
    int GInstrCount = 1;

    Function* addFunc(std::string& funcName,Type* retType,std::vector<Type*> paramsTypes);

    Function* getFunc(const std::string& funcName);
    //不是在全局，那么就把符号添加到对应函数的符号表
    void addSymbol(Function* func,std::string& symbolName,Symbol* symbol);

    void codegen(MachineUnit *mUnit, AsmBuilder *builder);
    void addInstr(Instruction* instr){
        global_instr.push_back(instr);
    }

    void Emit(std::ostream &os);

    void PrintSymbol(); // debug
};


#endif
