#include <iostream>
#include <ostream>
#include <string>
#include "antlr4-common.h"
#include "antlr4-runtime.h"
#include "BIFANGLexer.h"
#include "BIFANGParser.h"
#include "BIFANGVisitor.h"
#include "Backend/AsmBuilder.hpp"
#include "Backend/LinearScan.hpp"
#include "Backend/LiveAnalysis.hpp"
#include "Backend/MachineCodePass.hpp"
#include "Backend/MachineFunction.hpp"
#include "Pass/IROptimizer.h"

#ifndef TESTCASE_PATH
#define TESTCASE_PATH "../testcases"
#endif

using namespace std;

int main(int argc, const char* argv[]) {
    // 强制关闭 stdout 缓冲，确保打印立即显示
    setbuf(stdout, NULL);
    
    std::string testcase_path(TESTCASE_PATH);
    std::string test_file;
    std::string output_file;
    bool is_opt = true;
    if(argc == 1){
        test_file = testcase_path + "/testcase1.bf";
    }
    else if(argc == 2) {
        test_file = testcase_path + "/" + argv[1];
    }
    
    std::cerr << "[Main] Reading file: " << test_file << std::endl;
    std::ifstream stream(test_file);
    assert(stream);
    
    antlr4::ANTLRInputStream input(stream);
    BIFANGLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    BIFANGParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.program();
    
    BIFANGVisitor* visitor = new BIFANGVisitor();
    visitor->visit(tree);
    
    GlobalUnit *gu = visitor->globalUnit;
    
    if(is_opt) {
        std::cerr << "[Main] Starting Optimization..." << std::endl;
        IROptimizer *opt = new IROptimizer(gu);
        opt->Optimize();
        std::cerr << "[Main] Optimization Finished." << std::endl;
    }
    
    auto builder = make_unique<AsmBuilder>();
    auto mUnit = make_unique<MachineUnit>();
    
    std::string output_ll_file = std::string(TESTCASE_PATH) + "/"s + argv[1] +"_ir.ll"s;
    std::ofstream output_ll_stream(output_ll_file, std::ios::out | std::ios::trunc);
    
    std::cerr << "[Main] Starting IR Emit (Printing .ll file)..." << std::endl;
    // 【高度怀疑】这里会崩溃
    gu->Emit(output_ll_stream); 
    // 同时打印到屏幕一份，方便看死在哪里
    // gu->Emit(std::cout); 
    std::cerr << "[Main] IR Emit Finished." << std::endl;

    std::cerr << "[Main] Starting Backend CodeGen..." << std::endl;
    gu->codegen(mUnit.get(), builder.get());
    std::cerr << "[Main] Backend CodeGen Finished." << std::endl;
    
    fflush(stdout);
    
    for (auto mFunc : mUnit->func_list) {
        auto IR_func = mFunc->IR_func;
        for (auto bb : IR_func->getReversePostOrder()) {
            bb->mBlock->begin_no = MachineInstruction::counter;
            for (auto inst : bb->mBlock->inst_list) {
                inst->no = MachineInstruction::counter++;
                mFunc->no2inst.emplace_back(inst);
            }
            bb->mBlock->end_no = MachineInstruction::counter - 1;
        }
    }
    
    std::cerr << "[Main] Starting Register Allocation..." << std::endl;
    std::vector< std::unique_ptr<MachineCodePass> > mPasses;
    mPasses.emplace_back(new LiveAnalysis());
    mPasses.emplace_back(new LinearScan());
    for (auto &mPass : mPasses) {
        // [修复] 每次运行 Pass 前重置状态（如果有全局状态的话）
        mPass->pass(mUnit.get());
    }
    std::cerr << "[Main] Register Allocation Finished." << std::endl;

    if (output_file.empty()) output_file = std::string(TESTCASE_PATH) + "/"s + argv[1] +"_out.s"s;
    std::ios::sync_with_stdio(false);
    std::ofstream output_stream(output_file, std::ios::out | std::ios::trunc);
    mUnit->output(output_stream);
    
    std::cerr << "[Main] Compilation Success!" << std::endl;
    return 0;
}