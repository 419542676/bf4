
// Generated from D:/CLionProjects/BIFANG/BIFANGParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "BIFANGParserVisitor.h"


/**
 * This class provides an empty implementation of BIFANGParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  BIFANGParserBaseVisitor : public BIFANGParserVisitor {
public:

  virtual std::any visitProgram(BIFANGParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompUnit(BIFANGParser::CompUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecl(BIFANGParser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDecl(BIFANGParser::ConstDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBType(BIFANGParser::BTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDef(BIFANGParser::ConstDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstInitVal(BIFANGParser::ConstInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecl(BIFANGParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDef(BIFANGParser::VarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitVal(BIFANGParser::InitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(BIFANGParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncType(BIFANGParser::FuncTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncFParams(BIFANGParser::FuncFParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncFParam(BIFANGParser::FuncFParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(BIFANGParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockItem(BIFANGParser::BlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignStmt(BIFANGParser::AssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpStmt(BIFANGParser::ExpStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockStmt(BIFANGParser::BlockStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStmt(BIFANGParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfElseStmt(BIFANGParser::IfElseStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStmt(BIFANGParser::WhileStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStmt(BIFANGParser::BreakStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStmt(BIFANGParser::ContinueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStmt(BIFANGParser::ReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpParenthesis(BIFANGParser::ExpParenthesisContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallFuncExp(BIFANGParser::CallFuncExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLValExp(BIFANGParser::LValExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumberExp(BIFANGParser::NumberExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOpExp(BIFANGParser::UnaryOpExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPlusExp(BIFANGParser::PlusExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulExp(BIFANGParser::MulExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLtCond(BIFANGParser::LtCondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrCond(BIFANGParser::OrCondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpCond(BIFANGParser::ExpCondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndCond(BIFANGParser::AndCondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqCond(BIFANGParser::EqCondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLVal(BIFANGParser::LValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(BIFANGParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOp(BIFANGParser::UnaryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncRParams(BIFANGParser::FuncRParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParam(BIFANGParser::ParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstExp(BIFANGParser::ConstExpContext *ctx) override {
    return visitChildren(ctx);
  }


};

