#ifndef COMPILER_DEMO_MYVISITOR_H
#define COMPILER_DEMO_MYVISITOR_H

#include "BIFANGParserBaseVisitor.h"
#include "LLVM.h"
#include "Scope.h"
#include "Builder.h"
#include "Function.h"
#include "GlobalUnit.h"
#include <map>

class BIFANGVisitor : public BIFANGParserBaseVisitor {
public:
    Scope *globalScope;

    Scope *curScope;

    Function* curFunc;

    int scopeCounter;//作用域计数器

    ValueRef* zero = new Int_Const(0);

    stack<BasicBlock*> whileCondStk;

    stack<BasicBlock*> exitWhileStk;

    BasicBlock* TBlock;//用于短路时记录要跳转的块

    BasicBlock* FBlock;

    Builder *builder;

    GlobalUnit *globalUnit;

    BIFANGVisitor() {
        globalUnit = new GlobalUnit();
        curFunc = nullptr;
        curScope = nullptr;
        builder = new Builder(globalUnit);
    }


    virtual std::any visitProgram(BIFANGParser::ProgramContext *ctx) override;

    virtual std::any visitCompUnit(BIFANGParser::CompUnitContext *ctx) override;

    virtual std::any visitDecl(BIFANGParser::DeclContext *ctx) override;

    virtual std::any visitConstDecl(BIFANGParser::ConstDeclContext *ctx) override;

    virtual std::any visitBType(BIFANGParser::BTypeContext *ctx) override;

    virtual std::any visitConstDef(BIFANGParser::ConstDefContext *ctx) override;

    virtual std::any visitConstInitVal(BIFANGParser::ConstInitValContext *ctx) override;

    virtual std::any visitVarDecl(BIFANGParser::VarDeclContext *ctx) override;

    virtual std::any visitVarDef(BIFANGParser::VarDefContext *ctx) override;

    virtual std::any visitInitVal(BIFANGParser::InitValContext *ctx) override;

    virtual std::any visitFuncDef(BIFANGParser::FuncDefContext *ctx) override;

    virtual std::any visitFuncType(BIFANGParser::FuncTypeContext *ctx) override;

    virtual std::any visitFuncFParams(BIFANGParser::FuncFParamsContext *ctx) override;

    virtual std::any visitFuncFParam(BIFANGParser::FuncFParamContext *ctx) override;

    virtual std::any visitBlock(BIFANGParser::BlockContext *ctx) override;

    virtual std::any visitBlockItem(BIFANGParser::BlockItemContext *ctx) override;

    virtual std::any visitAssignStmt(BIFANGParser::AssignStmtContext *ctx) override;

    virtual std::any visitExpStmt(BIFANGParser::ExpStmtContext *ctx) override;

    virtual std::any visitBlockStmt(BIFANGParser::BlockStmtContext *ctx) override;

    virtual std::any visitIfStmt(BIFANGParser::IfStmtContext *ctx) override;

    virtual std::any visitIfElseStmt(BIFANGParser::IfElseStmtContext *ctx) override;

    virtual std::any visitWhileStmt(BIFANGParser::WhileStmtContext *ctx) override;

    virtual std::any visitBreakStmt(BIFANGParser::BreakStmtContext *ctx) override;

    virtual std::any visitContinueStmt(BIFANGParser::ContinueStmtContext *ctx) override;

    virtual std::any visitReturnStmt(BIFANGParser::ReturnStmtContext *ctx) override;

    virtual std::any visitExpParenthesis(BIFANGParser::ExpParenthesisContext *ctx) override;

    virtual std::any visitCallFuncExp(BIFANGParser::CallFuncExpContext *ctx) override;

    virtual std::any visitLValExp(BIFANGParser::LValExpContext *ctx) override;

    virtual std::any visitNumberExp(BIFANGParser::NumberExpContext *ctx) override;

    virtual std::any visitUnaryOpExp(BIFANGParser::UnaryOpExpContext *ctx) override;

    virtual std::any visitPlusExp(BIFANGParser::PlusExpContext *ctx) override;

    virtual std::any visitMulExp(BIFANGParser::MulExpContext *ctx) override;

    virtual std::any visitLtCond(BIFANGParser::LtCondContext *ctx) override;

    virtual std::any visitOrCond(BIFANGParser::OrCondContext *ctx) override;

    virtual std::any visitExpCond(BIFANGParser::ExpCondContext *ctx) override;

    virtual std::any visitAndCond(BIFANGParser::AndCondContext *ctx) override;

    virtual std::any visitEqCond(BIFANGParser::EqCondContext *ctx) override;

    virtual std::any visitLVal(BIFANGParser::LValContext *ctx) override;

    virtual std::any visitNumber(BIFANGParser::NumberContext *ctx) override;

    virtual std::any visitUnaryOp(BIFANGParser::UnaryOpContext *ctx) override;

    virtual std::any visitFuncRParams(BIFANGParser::FuncRParamsContext *ctx) override;

    virtual std::any visitParam(BIFANGParser::ParamContext *ctx) override;

    virtual std::any visitConstExp(BIFANGParser::ConstExpContext *ctx) override;

    void add_sylib_func();

    std::any getArrInitVal(Type* type, BIFANGParser::ConstInitValContext* ctx);
    std::any getArrInitVal(Type* type, BIFANGParser::InitValContext* ctx);
    vector<any> GiveMeAnArray(vector<BIFANGParser::ConstInitValContext*>& vals,int& idx,ArrayType* arr);
    vector<any> GiveMeAnArray(vector<BIFANGParser::InitValContext*>& vals,int& idx,ArrayType* arr);

};

struct sylib_func_t {
    std::string _funcName;
    Type_Enum _retType;
    vector<Type *> _paramsTypes;

    sylib_func_t(std::string funcName, Type_Enum retType, std::initializer_list<Type*> paramsTypes)
            : _funcName(std::move(funcName)), _retType(retType){
        for (auto type : paramsTypes) _paramsTypes.push_back(type);
    }
};


#endif
