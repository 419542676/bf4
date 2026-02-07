#include "GlobalUnit.h"
#include "Backend/AsmBuilder.hpp"
#include "Backend/MachineFunction.hpp"
#include "IRInstruction.h"
#include <memory>
#include <type_traits>
#include <iostream>
#include <bitset>

Function * GlobalUnit::addFunc(std::string& funcName, Type *retType, std::vector<Type *> paramsTypes) {
    FuncType * funcType = new FuncType(retType,paramsTypes);
    Function * function = new Function(funcName,funcType);
    func_table[funcName] = function;
    return function;
}

Function* GlobalUnit::getFunc(const std::string& funcName) {
    auto it = func_table.find(funcName);
    if (it == func_table.end()){
        std::cerr << "Function not exist!" << std::endl;
        throw std::exception();
    }
    return it->second;
}

void GlobalUnit::addSymbol(Function* func,std::string& symbolName,Symbol* symbol) {
    if(func == nullptr) // global symbol
        global_symbol_table[symbolName] = symbol;
    else
        func->addSymbol(symbolName,symbol);
}


void GlobalUnit::PrintSymbol() {
    std::cout << "Global Symbol:" << std::endl;
    for(const auto& it:global_symbol_table){
        std::cout << it.first << ": " << it.second->symbolType->getSize() << std::endl;
    }
    for(const auto& it:func_table){
        it.second->PrintSymbol();
    }
}


void GlobalUnit::codegen(MachineUnit *mUnit, AsmBuilder *builder) {
    std::cerr << "[DEBUG] GlobalUnit::codegen -> Start" << std::endl;
    
    if (!mUnit) { std::cerr << "[FATAL] mUnit is NULL" << std::endl; exit(1); }
    if (!builder) { std::cerr << "[FATAL] builder is NULL" << std::endl; exit(1); }

    builder->setUnit(mUnit);
    mUnit->IR_func_table = this->func_table;

    std::cerr << "[DEBUG] GlobalUnit::codegen -> Processing Global Instructions" << std::endl;
    for(auto ir: this->global_instr){
        if(auto addGlob = dynamic_cast<AddGlobalInstruction*>(ir)){
            addGlob->codegen(builder);
        }else{
            std::cerr << "[ERROR] Unknown global instruction" << std::endl;
            // throw NotImplemented("global var");
        }
    }

    std::cerr << "[DEBUG] GlobalUnit::codegen -> Iterating Functions" << std::endl;
    for (auto &[name, func] : func_table) {
        std::cerr << "[DEBUG] Checking function: " << name << std::endl;
        if (!func) {
            std::cerr << "[FATAL] Function pointer is NULL for: " << name << std::endl;
            continue;
        }
        if (func->block_list.size() > 0) {
            std::cerr << "[DEBUG] Calling codegen for function: " << name << std::endl;
            func->codegen(builder);
            std::cerr << "[DEBUG] Returned from codegen for function: " << name << std::endl;
        } else {
            std::cerr << "[DEBUG] Skipping empty function: " << name << std::endl;
        }
    }
    
    // fflush(stdout); // Removed, use stderr for debug
    std::cerr << "[DEBUG] GlobalUnit::codegen -> Processing Float Literals" << std::endl;
    
    for(auto& floatconst : IRInstruction::float_table){
        mUnit->float_literals << floatconst.first << ':' << std::endl;
        float f = floatconst.second;
        std::bitset<32> bits(*reinterpret_cast<unsigned int*>(&f));
        unsigned long decimal_value = static_cast<int>(bits.to_ulong());
        if (f < 0) {
            decimal_value = ~(decimal_value - 1);
            mUnit->float_literals << "\t.word\t" << "-" << decimal_value << '\n';
        } else{
            mUnit->float_literals << "\t.word\t" << decimal_value << '\n';
        }
    }
    std::cerr << "[DEBUG] GlobalUnit::codegen -> Finished" << std::endl;
}

void GlobalUnit::Emit(std::ostream &os) {
    for(auto instr: global_instr){
        instr->outPut(os);
    }
    for(auto it: this->func_table){
        it.second->Emit(os);
    }
}
