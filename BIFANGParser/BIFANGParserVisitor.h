
// Generated from D:/CLionProjects/BIFANG/BIFANGParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "BIFANGParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by BIFANGParser.
 */
class  BIFANGParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by BIFANGParser.
   */
    virtual std::any visitProgram(BIFANGParser::ProgramContext *context) = 0;

    virtual std::any visitCompUnit(BIFANGParser::CompUnitContext *context) = 0;

    virtual std::any visitDecl(BIFANGParser::DeclContext *context) = 0;

    virtual std::any visitConstDecl(BIFANGParser::ConstDeclContext *context) = 0;

    virtual std::any visitBType(BIFANGParser::BTypeContext *context) = 0;

    virtual std::any visitConstDef(BIFANGParser::ConstDefContext *context) = 0;

    virtual std::any visitConstInitVal(BIFANGParser::ConstInitValContext *context) = 0;

    virtual std::any visitVarDecl(BIFANGParser::VarDeclContext *context) = 0;

    virtual std::any visitVarDef(BIFANGParser::VarDefContext *context) = 0;

    virtual std::any visitInitVal(BIFANGParser::InitValContext *context) = 0;

    virtual std::any visitFuncDef(BIFANGParser::FuncDefContext *context) = 0;

    virtual std::any visitFuncType(BIFANGParser::FuncTypeContext *context) = 0;

    virtual std::any visitFuncFParams(BIFANGParser::FuncFParamsContext *context) = 0;

    virtual std::any visitFuncFParam(BIFANGParser::FuncFParamContext *context) = 0;

    virtual std::any visitBlock(BIFANGParser::BlockContext *context) = 0;

    virtual std::any visitBlockItem(BIFANGParser::BlockItemContext *context) = 0;

    virtual std::any visitAssignStmt(BIFANGParser::AssignStmtContext *context) = 0;

    virtual std::any visitExpStmt(BIFANGParser::ExpStmtContext *context) = 0;

    virtual std::any visitBlockStmt(BIFANGParser::BlockStmtContext *context) = 0;

    virtual std::any visitIfStmt(BIFANGParser::IfStmtContext *context) = 0;

    virtual std::any visitIfElseStmt(BIFANGParser::IfElseStmtContext *context) = 0;

    virtual std::any visitWhileStmt(BIFANGParser::WhileStmtContext *context) = 0;

    virtual std::any visitBreakStmt(BIFANGParser::BreakStmtContext *context) = 0;

    virtual std::any visitContinueStmt(BIFANGParser::ContinueStmtContext *context) = 0;

    virtual std::any visitReturnStmt(BIFANGParser::ReturnStmtContext *context) = 0;

    virtual std::any visitExpParenthesis(BIFANGParser::ExpParenthesisContext *context) = 0;

    virtual std::any visitCallFuncExp(BIFANGParser::CallFuncExpContext *context) = 0;

    virtual std::any visitLValExp(BIFANGParser::LValExpContext *context) = 0;

    virtual std::any visitNumberExp(BIFANGParser::NumberExpContext *context) = 0;

    virtual std::any visitUnaryOpExp(BIFANGParser::UnaryOpExpContext *context) = 0;

    virtual std::any visitPlusExp(BIFANGParser::PlusExpContext *context) = 0;

    virtual std::any visitMulExp(BIFANGParser::MulExpContext *context) = 0;

    virtual std::any visitLtCond(BIFANGParser::LtCondContext *context) = 0;

    virtual std::any visitOrCond(BIFANGParser::OrCondContext *context) = 0;

    virtual std::any visitExpCond(BIFANGParser::ExpCondContext *context) = 0;

    virtual std::any visitAndCond(BIFANGParser::AndCondContext *context) = 0;

    virtual std::any visitEqCond(BIFANGParser::EqCondContext *context) = 0;

    virtual std::any visitLVal(BIFANGParser::LValContext *context) = 0;

    virtual std::any visitNumber(BIFANGParser::NumberContext *context) = 0;

    virtual std::any visitUnaryOp(BIFANGParser::UnaryOpContext *context) = 0;

    virtual std::any visitFuncRParams(BIFANGParser::FuncRParamsContext *context) = 0;

    virtual std::any visitParam(BIFANGParser::ParamContext *context) = 0;

    virtual std::any visitConstExp(BIFANGParser::ConstExpContext *context) = 0;


};

