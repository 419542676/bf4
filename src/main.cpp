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


//自定义监听类，用于打印树结构
class MyParseTreeListener : public antlr4::tree::ParseTreeListener {
public:
    void enterEveryRule(antlr4::ParserRuleContext *ctx) override {
        // 在每个规则进入时调用
        std::cout << "Entering rule: " << ctx->getText() << std::endl;
    }

    void exitEveryRule(antlr4::ParserRuleContext *ctx) override {
        // 在每个规则退出时调用
        std::cout << "Exiting rule: " << ctx->getText() << std::endl;
    }
    void visitTerminal(antlr4::tree::TerminalNode *node) override {
        // 访问终结符时调用
        std::cout << "Visiting terminal: " << node->getText() << std::endl;
    }

    void visitErrorNode(antlr4::tree::ErrorNode *node) override {
        // 访问错误节点时调用
        std::cout << "Visiting error node: " << node->getText() << std::endl;
    }
    // 在这里可以添加其他需要实现的回调函数
};


int main(int argc, const char* argv[]) {
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
    std::ifstream stream(test_file);
    assert(stream);
    antlr4::ANTLRInputStream input(stream);
    BIFANGLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    BIFANGParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.program();
    // 创建自定义监听器实例打印解析树
    MyParseTreeListener listener;
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    BIFANGVisitor* visitor = new BIFANGVisitor();
    visitor->visit(tree);
    //中端
    GlobalUnit *gu = visitor->globalUnit;
   if(is_opt) {
       IROptimizer *opt = new IROptimizer(gu);
       opt->Optimize();
   }
    auto builder = make_unique<AsmBuilder>();
    auto mUnit = make_unique<MachineUnit>();
    std::string output_ll_file = std::string(TESTCASE_PATH) + "/"s + argv[1] +"_ir.ll"s;
    std::ofstream output_ll_stream(output_ll_file, std::ios::out | std::ios::trunc);
    gu->Emit(output_ll_stream);
    //后端
    gu->codegen(mUnit.get(), builder.get());
    fflush(stdout);
    for (auto mFunc : mUnit->func_list) {
        // 按基本块的拓扑序给指令编号
        auto IR_func = mFunc->IR_func;
        for (auto bb : IR_func->getReversePostOrder()) {
            bb->mBlock->begin_no = MachineInstruction::counter;
            for (auto inst : bb->mBlock->inst_list) {
                //开始编号
                inst->no = MachineInstruction::counter++;
                mFunc->no2inst.emplace_back(inst);
            }
            bb->mBlock->end_no = MachineInstruction::counter - 1;
        }
    }
    //寄存器分配
    std::vector< std::unique_ptr<MachineCodePass> > mPasses;
    mPasses.emplace_back(new LiveAnalysis());
    mPasses.emplace_back(new LinearScan());
    for (auto &mPass : mPasses) mPass->pass(mUnit.get());
    if (output_file.empty()) output_file = std::string(TESTCASE_PATH) + "/"s + argv[1] +"_out.s"s;
    std::ios::sync_with_stdio(false);
    std::ofstream output_stream(output_file, std::ios::out | std::ios::trunc);
    mUnit->output(output_stream);

    return 0;
}
