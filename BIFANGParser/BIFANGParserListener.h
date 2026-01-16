
// Generated from D:/CLionProjects/BIFANG/BIFANGParser.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "BIFANGParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by BIFANGParser.
 */
class  BIFANGParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(BIFANGParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(BIFANGParser::ProgramContext *ctx) = 0;

  virtual void enterCompUnit(BIFANGParser::CompUnitContext *ctx) = 0;
  virtual void exitCompUnit(BIFANGParser::CompUnitContext *ctx) = 0;

  virtual void enterDecl(BIFANGParser::DeclContext *ctx) = 0;
  virtual void exitDecl(BIFANGParser::DeclContext *ctx) = 0;

  virtual void enterConstDecl(BIFANGParser::ConstDeclContext *ctx) = 0;
  virtual void exitConstDecl(BIFANGParser::ConstDeclContext *ctx) = 0;

  virtual void enterBType(BIFANGParser::BTypeContext *ctx) = 0;
  virtual void exitBType(BIFANGParser::BTypeContext *ctx) = 0;

  virtual void enterConstDef(BIFANGParser::ConstDefContext *ctx) = 0;
  virtual void exitConstDef(BIFANGParser::ConstDefContext *ctx) = 0;

  virtual void enterConstInitVal(BIFANGParser::ConstInitValContext *ctx) = 0;
  virtual void exitConstInitVal(BIFANGParser::ConstInitValContext *ctx) = 0;

  virtual void enterVarDecl(BIFANGParser::VarDeclContext *ctx) = 0;
  virtual void exitVarDecl(BIFANGParser::VarDeclContext *ctx) = 0;

  virtual void enterVarDef(BIFANGParser::VarDefContext *ctx) = 0;
  virtual void exitVarDef(BIFANGParser::VarDefContext *ctx) = 0;

  virtual void enterInitVal(BIFANGParser::InitValContext *ctx) = 0;
  virtual void exitInitVal(BIFANGParser::InitValContext *ctx) = 0;

  virtual void enterFuncDef(BIFANGParser::FuncDefContext *ctx) = 0;
  virtual void exitFuncDef(BIFANGParser::FuncDefContext *ctx) = 0;

  virtual void enterFuncType(BIFANGParser::FuncTypeContext *ctx) = 0;
  virtual void exitFuncType(BIFANGParser::FuncTypeContext *ctx) = 0;

  virtual void enterFuncFParams(BIFANGParser::FuncFParamsContext *ctx) = 0;
  virtual void exitFuncFParams(BIFANGParser::FuncFParamsContext *ctx) = 0;

  virtual void enterFuncFParam(BIFANGParser::FuncFParamContext *ctx) = 0;
  virtual void exitFuncFParam(BIFANGParser::FuncFParamContext *ctx) = 0;

  virtual void enterBlock(BIFANGParser::BlockContext *ctx) = 0;
  virtual void exitBlock(BIFANGParser::BlockContext *ctx) = 0;

  virtual void enterBlockItem(BIFANGParser::BlockItemContext *ctx) = 0;
  virtual void exitBlockItem(BIFANGParser::BlockItemContext *ctx) = 0;

  virtual void enterAssignStmt(BIFANGParser::AssignStmtContext *ctx) = 0;
  virtual void exitAssignStmt(BIFANGParser::AssignStmtContext *ctx) = 0;

  virtual void enterExpStmt(BIFANGParser::ExpStmtContext *ctx) = 0;
  virtual void exitExpStmt(BIFANGParser::ExpStmtContext *ctx) = 0;

  virtual void enterBlockStmt(BIFANGParser::BlockStmtContext *ctx) = 0;
  virtual void exitBlockStmt(BIFANGParser::BlockStmtContext *ctx) = 0;

  virtual void enterIfStmt(BIFANGParser::IfStmtContext *ctx) = 0;
  virtual void exitIfStmt(BIFANGParser::IfStmtContext *ctx) = 0;

  virtual void enterIfElseStmt(BIFANGParser::IfElseStmtContext *ctx) = 0;
  virtual void exitIfElseStmt(BIFANGParser::IfElseStmtContext *ctx) = 0;

  virtual void enterWhileStmt(BIFANGParser::WhileStmtContext *ctx) = 0;
  virtual void exitWhileStmt(BIFANGParser::WhileStmtContext *ctx) = 0;

  virtual void enterBreakStmt(BIFANGParser::BreakStmtContext *ctx) = 0;
  virtual void exitBreakStmt(BIFANGParser::BreakStmtContext *ctx) = 0;

  virtual void enterContinueStmt(BIFANGParser::ContinueStmtContext *ctx) = 0;
  virtual void exitContinueStmt(BIFANGParser::ContinueStmtContext *ctx) = 0;

  virtual void enterReturnStmt(BIFANGParser::ReturnStmtContext *ctx) = 0;
  virtual void exitReturnStmt(BIFANGParser::ReturnStmtContext *ctx) = 0;

  virtual void enterExpParenthesis(BIFANGParser::ExpParenthesisContext *ctx) = 0;
  virtual void exitExpParenthesis(BIFANGParser::ExpParenthesisContext *ctx) = 0;

  virtual void enterCallFuncExp(BIFANGParser::CallFuncExpContext *ctx) = 0;
  virtual void exitCallFuncExp(BIFANGParser::CallFuncExpContext *ctx) = 0;

  virtual void enterLValExp(BIFANGParser::LValExpContext *ctx) = 0;
  virtual void exitLValExp(BIFANGParser::LValExpContext *ctx) = 0;

  virtual void enterNumberExp(BIFANGParser::NumberExpContext *ctx) = 0;
  virtual void exitNumberExp(BIFANGParser::NumberExpContext *ctx) = 0;

  virtual void enterUnaryOpExp(BIFANGParser::UnaryOpExpContext *ctx) = 0;
  virtual void exitUnaryOpExp(BIFANGParser::UnaryOpExpContext *ctx) = 0;

  virtual void enterPlusExp(BIFANGParser::PlusExpContext *ctx) = 0;
  virtual void exitPlusExp(BIFANGParser::PlusExpContext *ctx) = 0;

  virtual void enterMulExp(BIFANGParser::MulExpContext *ctx) = 0;
  virtual void exitMulExp(BIFANGParser::MulExpContext *ctx) = 0;

  virtual void enterLtCond(BIFANGParser::LtCondContext *ctx) = 0;
  virtual void exitLtCond(BIFANGParser::LtCondContext *ctx) = 0;

  virtual void enterOrCond(BIFANGParser::OrCondContext *ctx) = 0;
  virtual void exitOrCond(BIFANGParser::OrCondContext *ctx) = 0;

  virtual void enterExpCond(BIFANGParser::ExpCondContext *ctx) = 0;
  virtual void exitExpCond(BIFANGParser::ExpCondContext *ctx) = 0;

  virtual void enterAndCond(BIFANGParser::AndCondContext *ctx) = 0;
  virtual void exitAndCond(BIFANGParser::AndCondContext *ctx) = 0;

  virtual void enterEqCond(BIFANGParser::EqCondContext *ctx) = 0;
  virtual void exitEqCond(BIFANGParser::EqCondContext *ctx) = 0;

  virtual void enterLVal(BIFANGParser::LValContext *ctx) = 0;
  virtual void exitLVal(BIFANGParser::LValContext *ctx) = 0;

  virtual void enterNumber(BIFANGParser::NumberContext *ctx) = 0;
  virtual void exitNumber(BIFANGParser::NumberContext *ctx) = 0;

  virtual void enterUnaryOp(BIFANGParser::UnaryOpContext *ctx) = 0;
  virtual void exitUnaryOp(BIFANGParser::UnaryOpContext *ctx) = 0;

  virtual void enterFuncRParams(BIFANGParser::FuncRParamsContext *ctx) = 0;
  virtual void exitFuncRParams(BIFANGParser::FuncRParamsContext *ctx) = 0;

  virtual void enterParam(BIFANGParser::ParamContext *ctx) = 0;
  virtual void exitParam(BIFANGParser::ParamContext *ctx) = 0;

  virtual void enterConstExp(BIFANGParser::ConstExpContext *ctx) = 0;
  virtual void exitConstExp(BIFANGParser::ConstExpContext *ctx) = 0;


};

