#include "BIFANGVisitor.h"
#include "Utils.h"
#include <memory>

using namespace std;

ValueRef* getConstArrayValue(vector<ValueRef*>& idxs, Array_Const* constVal){
    any val = constVal->values;
    for(ValueRef* idx: idxs){
        assert(idx->type == IntConst);
        int i = stoi(idx->get_Ref());
        auto v = any_cast<vector<any>>(val);
        if(i >= v.size())
            return nullptr; // 越界了，说明此处未初始化，返回0
        else
            val = v[i];
    }
    return any_cast<ValueRef*>(val);
}

ValueRef * Parse_Any(std::any input){
    // 真是奇怪，将Pointer* any_cast ValueRef* 都不行
    if(input.type() == typeid(Pointer*)){
        return any_cast<Pointer*>(input);
    }
    else if(input.type() == typeid(Array*)){
        return any_cast<Array*>(input);
    }
    return any_cast<ValueRef*>(input);
}




Type* getTypeByStr(const string& type) {
    if (type == "void")
        return new Type(VOIDTYPE);
    if (type == "int")
        return new Type(INT32TYPE);
    if (type == "float")
        return new Type(FLOATTYPE);
    cerr <<"no type"<<endl;
    return nullptr;
}

bool block_ret;
Symbol * retVal;
BasicBlock * retBlock;
bool hasLogicCond = false;
bool isExpCond = false;

//program: compUnit;
std::any BIFANGVisitor::visitProgram(BIFANGParser::ProgramContext *ctx) {
    globalScope = new Scope(nullptr, 0);
    curScope = globalScope;
    //BIFANGParserBaseVisitor的visitProgram,调用visitChildren(ctx)
    BIFANGParserBaseVisitor::visitProgram(ctx);
    vector<Function *> func_vector;
    func_vector.reserve(globalUnit->func_table.size());
    for(auto & it : globalUnit->func_table){
        func_vector.push_back(it.second);
    }
    return nullptr;
}
//compUnit: (funcDef | decl)+ EOF;
std::any BIFANGVisitor::visitCompUnit(BIFANGParser::CompUnitContext *ctx) {
    return BIFANGParserBaseVisitor::visitChildren(ctx);
}
//decl: constDecl | varDecl;
std::any BIFANGVisitor::visitDecl(BIFANGParser::DeclContext *ctx) {
    return BIFANGParserBaseVisitor::visitDecl(ctx);
}
//constDecl: CONST bType constDef (COMMA constDef)* SEMICOLON;
std::any BIFANGVisitor::visitConstDecl(BIFANGParser::ConstDeclContext *ctx) {
    for(BIFANGParser::ConstDefContext* constDefContext : ctx->constDef()) {
        string constName = constDefContext->IDENT()->getText();
        if (constName.length() > 31) constName = constName.substr(0, 5) + "_";
        string type = ctx->bType()->getText();

        std::any constInitVal;
        ValueRef* constInitValRef;

        if (constDefContext->L_BRACKT().empty()) {//变量
            constInitVal = BIFANGVisitor::visit(constDefContext->constInitVal());
            constInitValRef = any_cast<ValueRef*>(constInitVal);
            //是否有赋值
            if (type == "int") {
                if(constInitValRef != nullptr) constInitValRef = BuildFPTrunc(builder,constInitValRef); // if init != null, try to convert initVal to int
                Symbol* symbol = curScope->addVar(builder, new Type(INT32TYPE), constName,true, constInitValRef);
                globalUnit->addSymbol(curFunc,symbol->name,symbol);
            } else {
                if(constInitValRef != nullptr) constInitValRef = BuildSitofp(builder,constInitValRef); // if init != null, try to convert initVal to float
                Symbol* symbol = curScope->addVar(builder, new Type(FLOATTYPE), constName, true,constInitValRef);
                globalUnit->addSymbol(curFunc,symbol->name,symbol);
            }

        } else {//数组
            vector<int> v;
            for(BIFANGParser::ConstExpContext* exp: constDefContext->constExp()){
                auto* ret = any_cast<ValueRef*>(BIFANGParserBaseVisitor::visitConstExp(exp));
                assert(ret->type == IntConst);
                v.push_back(stoi(ret->get_Ref()));
            }
            Type * arrType = new Type((type == "int")? INT32TYPE:FLOATTYPE);
            for(int i=v.size()-1;i>=0;i--){
                arrType = new ArrayType(arrType,v[i]);
            }
            //是否有赋值
            if (constDefContext->ASSIGN() != nullptr) {
                auto values = any_cast<vector<std::any> >(getArrInitVal(arrType,constDefContext->constInitVal()));
                constInitValRef = new Array_Const(values);
            } else {
                constInitValRef = nullptr;
            }
            Symbol* symbol = curScope->addVar(builder,arrType,constName,true,constInitValRef);
            globalUnit->addSymbol(curFunc,symbol->name,symbol);
        }
    }
    return nullptr;
}
//bType: INT | FLOAT;
std::any BIFANGVisitor::visitBType(BIFANGParser::BTypeContext *ctx) {
    return BIFANGParserBaseVisitor::visitBType(ctx);
}
//constDef: IDENT (L_BRACKT constExp R_BRACKT)* ASSIGN constInitVal;
std::any BIFANGVisitor::visitConstDef(BIFANGParser::ConstDefContext *ctx) {
    return BIFANGParserBaseVisitor::visitConstDef(ctx);
}
//constInitVal: constExp | L_BRACE (constInitVal (COMMA constInitVal)*)? R_BRACE;
std::any BIFANGVisitor::visitConstInitVal(BIFANGParser::ConstInitValContext *ctx) {
    return BIFANGParserBaseVisitor::visitConstInitVal(ctx);
}



//varDecl: bType varDef (COMMA varDef)* SEMICOLON;
std::any BIFANGVisitor::visitVarDecl(BIFANGParser::VarDeclContext *ctx) {
    for(BIFANGParser::VarDefContext* varDefContext : ctx->varDef()) {
        string varName = varDefContext->IDENT()->getText();
        //处理变量名过长
        if (varName.length() > 31) varName = varName.substr(0, 5) + "_";

        string type = ctx->bType()->getText();
        ValueRef* varInitValRef;

        //如果变量不是数组
        if (varDefContext->L_BRACKT().empty()) {
            if (varDefContext->ASSIGN() != nullptr) {
                varInitValRef = any_cast<ValueRef*>(BIFANGVisitor::visit(varDefContext->initVal()));
            } else {
                varInitValRef = nullptr;
            }

            //Alloca-Init-Def
            if (type == "int") {
                if(varInitValRef != nullptr) varInitValRef = BuildFPTrunc(builder,varInitValRef); // if init != null, convert initVal to int
                //向curScope中创建并添加一个变量
                Symbol* symbol = curScope->addVar(builder, new Type(INT32TYPE), varName,false, varInitValRef);
                //向curFunc或全局中创建并添加一个变量
                globalUnit->addSymbol(curFunc,symbol->name,symbol);
            } else { // float
                if(varInitValRef != nullptr) varInitValRef = BuildSitofp(builder,varInitValRef); // if init != null, convert initVal to float
                //向curScope中创建并添加一个变量
                Symbol* symbol = curScope->addVar(builder, new Type(FLOATTYPE), varName,false, varInitValRef);
                //向curFunc或全局中创建并添加一个变量
                globalUnit->addSymbol(curFunc,symbol->name,symbol);
            }
        } else {//数组赋值情况额外考虑
            vector<int> v;
            for(BIFANGParser::ConstExpContext* exp: varDefContext->constExp()){
                auto* ret = any_cast<ValueRef*>(BIFANGVisitor::visitConstExp(exp));
                assert(ret->type == IntConst);
                v.push_back(stoi(ret->get_Ref()));
            }
            Type * arrType = new Type((type == "int")? INT32TYPE:FLOATTYPE);
            for(int i=v.size()-1;i>=0;i--){
                arrType = new ArrayType(arrType,v[i]);
            }

            if (varDefContext->ASSIGN() != nullptr) {
                auto values = any_cast<vector<std::any>>(getArrInitVal(arrType,varDefContext->initVal()));
                varInitValRef = new Array_Const(values);
            } else {
                varInitValRef = nullptr;
            }
            Symbol* symbol = curScope->addVar(builder,arrType,varName,false,varInitValRef);
            globalUnit->addSymbol(curFunc,symbol->name,symbol);
        }
    }
    return nullptr;
}


//varDef: IDENT (L_BRACKT constExp R_BRACKT)* (ASSIGN initVal)?;
std::any BIFANGVisitor::visitVarDef(BIFANGParser::VarDefContext *ctx) {
    return BIFANGParserBaseVisitor::visitVarDef(ctx);
}
//initVal: exp | L_BRACE (initVal (COMMA initVal)*)? R_BRACE;
std::any BIFANGVisitor::visitInitVal(BIFANGParser::InitValContext *ctx) {
    return BIFANGParserBaseVisitor::visitInitVal(ctx);
}


//funcDef: funcType IDENT L_PAREN funcFParams? R_PAREN block;
std::any BIFANGVisitor::visitFuncDef(BIFANGParser::FuncDefContext *ctx) {
    std::string funcName = ctx->IDENT()->getText();
    ///处理函数头和返回值
    //生成返回值类型
    string retTypeCtx = ctx->funcType()->getText();
    Type* retType = getTypeByStr(retTypeCtx);

    //生成参数类型
    std::string args;
    vector<Type*> paramsTypes;
    int paramsCnt = 0;
    //判断是否有参数
    if (ctx->funcFParams() != nullptr) {
        paramsCnt = ctx->funcFParams()->funcFParam().size();
        for (int i = 0; i < paramsCnt; ++i) {
            Type* paramType = getTypeByStr(ctx->funcFParams()->funcFParam(i)->bType()->getText());
            //判断参数是否是数组，如果参数是数组类型，还需要计算数组的维度，
            // 并创建相应的 ArrayType 和 PointerType。
            if (!ctx->funcFParams()->funcFParam(i)->L_BRACKT().empty()) {
                vector<BIFANGParser::ExpContext*> v = ctx->funcFParams()->funcFParam(i)->exp();
                for(int j = v.size()-1; j >= 0; j--){
                    auto* size = any_cast<ValueRef*>(BIFANGVisitor::visit(v[j]));
                    assert(size->type == IntConst);
                    paramType = new ArrayType(paramType,stoi(size->get_Ref()));
                }
                paramType = new PointerType(paramType);
            }
            paramsTypes.push_back(paramType);
        }

    }

    //生成函数类型
    Function* function = globalUnit->addFunc(funcName, retType, paramsTypes);
    curFunc = function;
    builder->curFunc = function;

    //为函数创建开始基本块、入口基本块以及返回基本块
    string retName = funcName + "Ret";
    retBlock = new BasicBlock(retName,function);
    //startBlock作用是创建类似define i32 @add(i32 %a, i32 %b)的IR
    string startName = funcName + "Start";
    BasicBlock* startBlock = builder->AppendBasicBlock(curFunc,startName);
    curFunc->entry = startBlock;

    string entryName = funcName + "Entry";
    BasicBlock* entryBlock = builder->AppendBasicBlock(curFunc,entryName);

    //构建函数
    builder->PositionBuilderAtEnd(entryBlock);
    // 从这里开始进入函数，临时变量计数器清零
    Utils::setTempCounter(0);

    //新建作用域，把返回值的变量创建出来，并把它加进curScope的符号表，把它加进curFunc或全局的符号表中
    curScope = new Scope(curScope, ++scopeCounter);
    string name = "retVal";
    if(retType->type == VOIDTYPE){
        retVal = nullptr;
    }
    else if(retType->type == INT32TYPE){
        //向curScope中创建并添加一个变量，并返回一个指向该变量的符号（Symbol）指针
        retVal = curScope->addVar(builder,retType,name,false,new Int_Const(0));
        //向curFunc或全局中创建并添加一个变量（具体看curFunc在全局还是局部函数）
        globalUnit->addSymbol(curFunc,retVal->name,retVal);
    }
    else{ // float
        //向curScope创建并添加一个变量
        retVal = curScope->addVar(builder,retType,name,false,new Float_Const(0.0));
        //向curFunc或全局中创建并添加一个变量
        globalUnit->addSymbol(curFunc,retVal->name,retVal);
    }
    ///把函数参数添加到符号表
    for (int i = 0; i < paramsCnt; ++i) {
        string paramName = ctx->funcFParams()->funcFParam(i)->IDENT()->getText();
        Type* paramType = paramsTypes[i];

        ValueRef* argVal;

        if (paramType->type == INT32TYPE)
            argVal = new Int_Var();
        else if (paramType->type == FLOATTYPE)
            argVal = new Float_Var();
        else //POINTERTYPE
            argVal = new Pointer((PointerType*)paramType);
        //向curScope创建并添加一个变量
        Symbol* symbol = curScope->addVar(builder, paramType, paramName, false, argVal);
        //向curFunc或全局中创建并添加一个变量
        globalUnit->addSymbol(curFunc,symbol->name,symbol);

        args += i==0 ? paramType->getTypeName()+" "+argVal->get_Ref() : ", "+paramType->getTypeName()+" "+argVal->get_Ref();
    }
    //define i32 @func(i32 %1,%float %2){
    std::string funcDef1 = "define " + retType->getTypeName() + " @" + funcName + "(" + args + ")" + " {\n";
    function->debugInfo = funcDef1;
    ///处理函数体
    //访问函数体
    block_ret = false;
    BIFANGVisitor::visitBlock(ctx->block());

    //如果函数没有return，则手动插入跳转到返回块的BR指令
    if (!block_ret){
        BuildBr(builder,retBlock);
    }
    //在startBlock的末尾构建跳转到entryBlock的无条件分支指令
    builder->PositionBuilderAtEnd(startBlock);
    BuildBr(builder,entryBlock);
    //将构建位置移动到返回基本快的末尾
    builder->PositionBuilderAtEnd(retBlock);
    if(retType->type == VOIDTYPE){
        //插入ret指令
        BuildRet(builder,nullptr);
    }
    else{
        //Load retVal的值然后插入ret retVal 指令
        ValueRef * ret = BuildLoad(builder,retVal);
        BuildRet(builder,ret);
    }
    //恢复环境
    curFunc->block_list.push_back(retBlock);
    curScope = curScope->super;
    curFunc = nullptr;
    builder->PositionBuilderAtEnd(nullptr);

    return "";
}


//funcType: VOID | INT | FLOAT;
std::any BIFANGVisitor::visitFuncType(BIFANGParser::FuncTypeContext *ctx) {
    return BIFANGParserBaseVisitor::visitFuncType(ctx);
}
//funcFParams: funcFParam (COMMA funcFParam)*;
std::any BIFANGVisitor::visitFuncFParams(BIFANGParser::FuncFParamsContext *ctx) {
    return BIFANGParserBaseVisitor::visitFuncFParams(ctx);
}
//funcFParam: bType IDENT (L_BRACKT R_BRACKT (L_BRACKT exp R_BRACKT)*)?;
std::any BIFANGVisitor::visitFuncFParam(BIFANGParser::FuncFParamContext *ctx) {
    return BIFANGParserBaseVisitor::visitFuncFParam(ctx);
}



//block: L_BRACE blockItem* R_BRACE;
std::any BIFANGVisitor::visitBlock(BIFANGParser::BlockContext *ctx) {
    block_ret = false;
    curScope = new Scope(curScope, ++scopeCounter);
    BIFANGParserBaseVisitor::visitBlock(ctx);
    curScope = curScope->super;
    //block_ret = false;
    return nullptr;
}
//blockItem: decl | stmt;
std::any BIFANGVisitor::visitBlockItem(BIFANGParser::BlockItemContext *ctx) {
    if (block_ret)
        return nullptr;

    return BIFANGParserBaseVisitor::visitBlockItem(ctx);
}

//stmt: lVal ASSIGN exp SEMICOLON
std::any BIFANGVisitor::visitAssignStmt(BIFANGParser::AssignStmtContext *ctx) {
    std::any lVal = BIFANGVisitor::visitLVal(ctx->lVal());
    std::any rVal = BIFANGVisitor::visit(ctx->exp());

    auto rValRef = any_cast<ValueRef*>(rVal);
    //如果左值是变量
    if(lVal.type() == typeid(Symbol*)){
        auto lValSymbol = any_cast<Symbol*>(lVal);
        if(lValSymbol->symbolType->type == INT32TYPE){
            rValRef = BuildFPTrunc(builder,rValRef); // (if rVal = float) float -> int
        }
        else if(lValSymbol->symbolType->type == FLOATTYPE){
            rValRef = BuildSitofp(builder,rValRef); // (if rVal = int) int -> float
        }
        BuildStore(builder, lValSymbol,rValRef);
    }
        //如果左值是指针
    else{
        auto lValSymbol = Parse_Any(lVal);
        if(((Pointer*)lValSymbol)->pointerType->elementType->type == INT32TYPE){
            rValRef = BuildFPTrunc(builder,rValRef); // (if rVal = float) float -> int
        }
        else if(((Pointer*)lValSymbol)->pointerType->elementType->type == FLOATTYPE){
            rValRef = BuildSitofp(builder,rValRef); // (if rVal = int) int -> float
        }
        BuildStore(builder, ((Pointer*)lValSymbol),rValRef);
    }

    return nullptr;
}


//stmt: exp? SEMICOLON
std::any BIFANGVisitor::visitExpStmt(BIFANGParser::ExpStmtContext *ctx) {
    return BIFANGParserBaseVisitor::visitExpStmt(ctx);
}
//stmt: block
std::any BIFANGVisitor::visitBlockStmt(BIFANGParser::BlockStmtContext *ctx) {
    return BIFANGParserBaseVisitor::visitBlockStmt(ctx);
}


//stmt: IF L_PAREN cond R_PAREN stmt
std::any BIFANGVisitor::visitIfStmt(BIFANGParser::IfStmtContext *ctx) {
    string trueBlkName = "if.then";
    auto* trueBlock = new BasicBlock(trueBlkName, curFunc);
    string nextBlkName = "if.end";
    auto* nextBlock = new BasicBlock(nextBlkName, curFunc);

    TBlock = trueBlock;
    FBlock = nextBlock;


    any condRes = BIFANGVisitor::visit(ctx->cond());

    if (!hasLogicCond) {
        auto* condVal = any_cast<ValueRef*>(condRes);
        ValueRef* condBool = BuildCmp(builder, condVal, zero, NE);
        BuildCondBr(builder, condBool, trueBlock, nextBlock);
    } else {
        hasLogicCond = false;
    }

    //if_true

    curFunc->appendBlock(trueBlock);
    builder->PositionBuilderAtEnd(trueBlock);

    //如果stmt没有返回语句，则生成无条件跳转指令，将控制流转移到下一步执行的块。
    BIFANGVisitor::visit(ctx->stmt());
    if (!block_ret)
        BuildBr(builder, nextBlock);

    block_ret = false;

    //if_next

    curFunc->appendBlock(nextBlock);
    builder->PositionBuilderAtEnd(nextBlock);

    return nullptr;
}
//stmt: IF L_PAREN cond R_PAREN stmt ELSE stmt
std::any BIFANGVisitor::visitIfElseStmt(BIFANGParser::IfElseStmtContext *ctx) {
    string trueBlkName = "if.then";
    auto* trueBlock = new BasicBlock(trueBlkName, curFunc);
    string falseBlkName = "if.else";
    auto* falseBlock = new BasicBlock(falseBlkName, curFunc);
    string nextBlkName = "if.end";
    BasicBlock* nextBlock = nullptr;

    TBlock = trueBlock;
    FBlock = falseBlock;


    any condRes = BIFANGVisitor::visit(ctx->cond());

    if (!hasLogicCond) {
        auto* condVal = any_cast<ValueRef*>(condRes);
        ValueRef* condBool = BuildCmp(builder, condVal, zero, NE);
        BuildCondBr(builder, condBool, trueBlock, falseBlock);
    } else {
        hasLogicCond = false;
    }


    bool blk_ret1, blk_ret2;
    //if_true

    curFunc->appendBlock(trueBlock);
    builder->PositionBuilderAtEnd(trueBlock);


    BIFANGVisitor::visit(ctx->stmt(0));
    blk_ret1 = block_ret;
    block_ret = false;

    //如果第一个stmt没直接返回，就生成跳转指令，将控制流转移到下一步执行的块
    if (!blk_ret1) {
        nextBlock = new BasicBlock(nextBlkName, curFunc);
        BuildBr(builder, nextBlock);
    }


    //if_false
    curFunc->appendBlock(falseBlock);
    builder->PositionBuilderAtEnd(falseBlock);

    //访问第二个语句块（ctx->stmt(1)）若没有返回语句，则生成跳转指令，将控制流转移到下一步执行的块
    BIFANGVisitor::visit(ctx->stmt(1));
    blk_ret2 = block_ret;
    block_ret = false;


    if (!blk_ret2) {
        if (nextBlock == nullptr)
            nextBlock = new BasicBlock(nextBlkName, curFunc);
        BuildBr(builder, nextBlock);
    }

    //if_next
    if (nextBlock != nullptr){
        curFunc->appendBlock(nextBlock);
        builder->PositionBuilderAtEnd(nextBlock);
    }

    block_ret = blk_ret1 && blk_ret2;
    return nullptr;
}
//stmt: WHILE L_PAREN cond R_PAREN stmt
std::any BIFANGVisitor::visitWhileStmt(BIFANGParser::WhileStmtContext *ctx) {
    //    string condBlkName = "whileCond";
//    BasicBlock* condBlock = builder->AppendBasicBlock(curFunc, condBlkName);
//    BuildBr(builder, condBlock);
//
//    string bodyBlkName = "whileBody";
//    auto* bodyBlock = new BasicBlock(bodyBlkName, curFunc);
//
//    string nextBlkName = "whileNext";
//    auto* nextBlock = new BasicBlock(nextBlkName, curFunc);
//
//
//    TBlock = bodyBlock;
//    FBlock = nextBlock;
//
//    //while_cond
//    builder->PositionBuilderAtEnd(condBlock);
//    any condRes = BIFANGVisitor::visit(ctx->cond());
//
//    if (!hasLogicCond) {
//        auto* condVal = any_cast<ValueRef*>(condRes);
//        ValueRef* condBool = BuildCmp(builder, condVal, zero, NE);
//        BuildCondBr(builder, condBool, bodyBlock, nextBlock);
//    } else {
//        hasLogicCond = false;
//    }
//
//    //while_body
//    curFunc->appendBlock(bodyBlock);
//    builder->PositionBuilderAtEnd(bodyBlock);
//
//    whileCondStk.push(condBlock);
//    exitWhileStk.push(nextBlock);
//    BIFANGVisitor::visit(ctx->stmt());
//    whileCondStk.pop();
//    exitWhileStk.pop();
//
//    if (!block_ret)
//        BuildBr(builder, condBlock);
//
//    //exit_while
//    curFunc->appendBlock(nextBlock);
//    builder->PositionBuilderAtEnd(nextBlock);
//    block_ret = false;
//    return nullptr;

    // do-while

    string condBlkName = "whileCond";
    BasicBlock* condBlock = builder->AppendBasicBlock(curFunc, condBlkName);
    BuildBr(builder, condBlock);

    string bodyBlkName = "doWhileBody";
    auto bodyBlock = new BasicBlock(bodyBlkName, curFunc);

    string whileCondBlkName = "doWhileCond";
    auto doWhileCondBlock = new BasicBlock(whileCondBlkName, curFunc);

    string nextBlkName = "whileNext";
    auto nextBlock = new BasicBlock(nextBlkName, curFunc);

    TBlock = bodyBlock;
    FBlock = nextBlock;

    //while_cond 先定位到循环条件的基本块
    builder->PositionBuilderAtEnd(condBlock);
    any condRes = BIFANGVisitor::visit(ctx->cond());
    //判断是否存在逻辑条件。如果不存在，将条件的值转为整数，
    //然后构建比较指令，根据条件跳转到循环体或者循环结束的基本块。
    if (!hasLogicCond) {
        auto* condVal = any_cast<ValueRef*>(condRes);
        ValueRef* zext = BuildZext(builder,condVal);
        ValueRef* condBool = BuildCmp(builder, zext, zero, NE);
        BuildCondBr(builder, condBool, bodyBlock, nextBlock);
    } else {
        hasLogicCond = false;
    }

    //while_body
    curFunc->appendBlock(bodyBlock);
    builder->PositionBuilderAtEnd(bodyBlock);

    whileCondStk.push(doWhileCondBlock);
    exitWhileStk.push(nextBlock);
    BIFANGVisitor::visit(ctx->stmt());
    whileCondStk.pop();
    exitWhileStk.pop();

    if (!block_ret) {
        BuildBr(builder, doWhileCondBlock);
    }

    //do_while_cond
    curFunc->appendBlock(doWhileCondBlock);
    builder->PositionBuilderAtEnd(doWhileCondBlock);

    TBlock = bodyBlock;
    FBlock = nextBlock;

    any cond = BIFANGVisitor::visit(ctx->cond());
    if (!hasLogicCond) {
        auto condVal = any_cast<ValueRef*>(cond);
        auto condBool = BuildCmp(builder, condVal, zero, NE);
        BuildCondBr(builder, condBool, bodyBlock, nextBlock);
    } else {
        hasLogicCond = false;
    }

    //exit_while
    curFunc->appendBlock(nextBlock);
    builder->PositionBuilderAtEnd(nextBlock);
    block_ret = false;
    return nullptr;
}
//stmt: BREAK SEMICOLON
std::any BIFANGVisitor::visitBreakStmt(BIFANGParser::BreakStmtContext *ctx) {
    block_ret = true;
    BuildBr(builder, exitWhileStk.top());
    return nullptr;
}
//stmt: CONTINUE SEMICOLON
std::any BIFANGVisitor::visitContinueStmt(BIFANGParser::ContinueStmtContext *ctx) {
    block_ret = true;
    BuildBr(builder, whileCondStk.top());
    return nullptr;
}
//stmt: RETURN (exp)? SEMICOLON
std::any BIFANGVisitor::visitReturnStmt(BIFANGParser::ReturnStmtContext *ctx) {
    block_ret = true;
    ValueRef* ret = nullptr;
    if (ctx->exp() != nullptr)
        ret = any_cast<ValueRef*>(BIFANGVisitor::visit(ctx->exp()));
    if(curFunc->funcType->retType->type == INT32TYPE){
        //如果ret是浮点数则把整数部分截断返回
        ret = BuildFPTrunc(builder,ret);
    }
    else if(curFunc->funcType->retType->type == FLOATTYPE){
        //有符号整数到浮点数转换
        ret = BuildSitofp(builder,ret);
    }
    //函数返回值类型不为void
    if(ret != nullptr) {
        BuildStore(builder, retVal, ret);
    }
    BuildBr(builder,retBlock);
    return nullptr;
}
//exp: L_PAREN exp R_PAREN
std::any BIFANGVisitor::visitExpParenthesis(BIFANGParser::ExpParenthesisContext *ctx) {
    return BIFANGVisitor::visit(ctx->exp());
}
//exp: lVal
std::any BIFANGVisitor::visitCallFuncExp(BIFANGParser::CallFuncExpContext *ctx) {
    string funcName = ctx->IDENT()->getText();
    Function *func = globalUnit->getFunc(funcName);

    vector<ValueRef*> args;
    int argsCnt;
    if (ctx->funcRParams() != nullptr) {
        argsCnt = ctx->funcRParams()->param().size();
        auto argsType = func->funcType->arguments;
        // assert(argsType.size() == argsCnt);
        for(int i = 0; i < argsCnt; ++i) {
            ValueRef* arg = Parse_Any(BIFANGVisitor::visit(ctx->funcRParams()->param(i)));

            auto argTy = argsType[i]->type;
            if (argTy == INT32TYPE)
                arg = BuildFPTrunc(builder, arg);
            else if (argTy == FLOATTYPE)
                arg = BuildSitofp(builder, arg);

            Type* type = argsType[i];
            if(type->type == POINTERTYPE && type->getDimension() < arg->getType()->getDimension()){
                vector<ValueRef*> v;
                for(int j=0;j<arg->getType()->getDimension() - type->getDimension(); ++j){
                    v.push_back(new Int_Const(0));
                }
                arg = BuildGEP(builder,arg,v);
            }
            args.push_back(arg);
        }
    }

    if(funcName == "starttime" || funcName == "stoptime"){
        args.push_back(new Int_Const(0));
    }

    return BuildCall(builder, func, args);
}
//exp: number
std::any BIFANGVisitor::visitLValExp(BIFANGParser::LValExpContext *ctx) {
    // LVal和LValExp一个是左值一个是右值，考虑分开实现
    string varName = ctx->lVal()->IDENT()->getText();
    if(varName.length() > 31) varName = varName.substr(0, 5) + "_";
    Symbol * symbol = curScope->getVar(varName);
    //如果左值是符号
    if (ctx->lVal()->exp().empty()) {
        if(symbol->symbolType->type != ARRAYTYPE){
            //常量
            if(symbol->is_const){
                return symbol->constVal;
            }
            else{ //不是常量
                return BuildLoad(builder,symbol);
            }
        }
            //数组符号,构建数组的指针
        else{
            vector<ValueRef*> v;
            return BuildGEP(builder,symbol, v);
        }
    }
        //如果左值包含下标
    else {
        vector<ValueRef*> indices;
        bool all_const = symbol->is_const; // 对应数组为const,且所有下标均为const情况

        for(BIFANGParser::ExpContext* exp: ctx->lVal()->exp()) {
            auto* idx = any_cast<ValueRef*>(BIFANGVisitor::visit(exp));
            all_const &= idx->type == IntConst;
            indices.push_back(idx);

        }
        bool get_val = symbol->symbolType->getDimension() == indices.size(); // 用于判断下标个数是否等于数组/指针维度，如果相等则取值，否则返回指针
        // 如果是const数组和const下标，则直接返回数组中相应值
        if(get_val && all_const){
            ValueRef* ret = getConstArrayValue(indices,(Array_Const*)symbol->constVal);
            if(ret != nullptr){
                return ret;
            }
            else{ //未初始化的数组则返回0,然后创建一个
                Type * temp = symbol->symbolType;
                assert(temp->type == ARRAYTYPE);
                for(int i=0;i<indices.size();i++){
                    temp = ((ArrayType*)temp) -> elementType;
                }
                if(temp->type == INT32TYPE)
                    return new Int_Const(0);
                else
                    return new Float_Const(0.0);
            }
        }
        // 如果不是const数组或下标不全为const，通过BuildGEP函数构建对数组或指针的指针，
        // 返回指针或通过BuildLoad函数加载相应的值。
        ValueRef *ptr;
        if (symbol->symbolType->type == POINTERTYPE) {
            ValueRef* varPtr = BuildLoad(builder, symbol);
            ptr = Parse_Any(BuildGEP(builder, varPtr, indices));
        } else { //symbol->symbolType->type == ARRAYTYPE
            ptr = Parse_Any(BuildGEP(builder, symbol, indices));
        }

        if(get_val){
            return BuildLoad(builder,dynamic_cast<Pointer*>(ptr));
        }
        else{
            return ptr;
        }
    }
}
//exp: IDENT L_PAREN funcRParams? R_PAREN
std::any BIFANGVisitor::visitNumberExp(BIFANGParser::NumberExpContext *ctx) {
    string valCtx;
    ValueRef* val;

    if (ctx->number()->INTEGER_CONST() != nullptr) {
        int intVal;
        valCtx = ctx->number()->INTEGER_CONST()->getText();
        // if (valCtx.starts_with("0x") || valCtx.starts_with("0X"))
        if (valCtx.substr(0, 2) == "0x" || valCtx.substr(0, 2) == "0X")
            intVal = stoi(valCtx, nullptr, 16);
        else if (valCtx[0] == '0')
            intVal = stoi(valCtx, nullptr, 8);
        else
            intVal = stoi(valCtx);
        val = new Int_Const(intVal);
    } else {
        float floatVal;
        valCtx = ctx->number()->FLOAT_CONST()->getText();
        floatVal = stof(valCtx);
        val = new Float_Const(floatVal);
    }

    return val;
}
//exp: unaryOp exp
std::any BIFANGVisitor::visitUnaryOpExp(BIFANGParser::UnaryOpExpContext *ctx) {
    auto* expVal = any_cast<ValueRef*>(BIFANGVisitor::visit(ctx->exp()));

    ValueRef* res;
    //默认expVal是int类型
    if (ctx->unaryOp()->PLUS() != nullptr)
        res = expVal;
    if (ctx->unaryOp()->MINUS() != nullptr)
        res = BuildNeg(builder, expVal);
    else if (ctx->unaryOp()->NOT() != nullptr)
        res = BuildNot(builder, expVal);


    return res;
}
//exp: exp (PLUS | MINUS) exp
std::any BIFANGVisitor::visitPlusExp(BIFANGParser::PlusExpContext *ctx) {
    //BIFANGParser::ExpContext *exp0 = ctx->exp(0);
    //std :: any ans = BIFANGVisitor::visit(exp0);

    auto* lhs = any_cast<ValueRef*>(BIFANGVisitor::visit(ctx->exp(0)));

    auto* rhs = any_cast<ValueRef*>(BIFANGVisitor::visit(ctx->exp(1)));
    ValueRef* res;
    //cerr<<lhs->get_Ref()<<" "<<rhs->get_Ref()<<endl;

    //默认lhs和rhs全是int类型
    if (ctx->PLUS()!= nullptr) {

        res = BuildAdd(builder, lhs, rhs);

    } else if (ctx->MINUS() != nullptr) {
        res = BuildSub(builder, lhs, rhs);
    }

    return res;
}
//exp: exp (MUL | DIV | MOD) exp
std::any BIFANGVisitor::visitMulExp(BIFANGParser::MulExpContext *ctx) {
    auto* lhs = any_cast<ValueRef*>(BIFANGVisitor::visit(ctx->exp(0)));
    auto* rhs = any_cast<ValueRef*>(BIFANGVisitor::visit(ctx->exp(1)));
    ValueRef* res;
    //默认lhs和rhs全是int类型
    if (ctx->MUL() != nullptr) {
        res = BuildMul(builder, lhs, rhs);
    } else if (ctx->DIV() != nullptr) {
        res = BuildDiv(builder, lhs, rhs);
    } else if (ctx->MOD() != nullptr) {
        res = BuildMod(builder, lhs, rhs);
    }
    return res;
}
//cond: cond (LT | GT | LE | GE) cond
std::any BIFANGVisitor::visitLtCond(BIFANGParser::LtCondContext *ctx) {
    //cerr<<"visitLtCond"<<endl;
    auto* lhs = any_cast<ValueRef*>(BIFANGVisitor::visit(ctx->cond(0)));
    auto* rhs = any_cast<ValueRef*>(BIFANGVisitor::visit(ctx->cond(1)));

    if (ctx->LT() != nullptr)
        return BuildCmp(builder, lhs, rhs,LT);
    else if (ctx->GT() != nullptr)
        return BuildCmp(builder, lhs, rhs,GT);
    else if (ctx->LE() != nullptr)
        return BuildCmp(builder, lhs, rhs,LE);
    else if (ctx->GE() != nullptr)
        return BuildCmp(builder, lhs, rhs,GE);
    else {
        cerr << "you should not arrive here!"<<endl;
        return nullptr;
    }
}
//cond: cond OR cond
std::any BIFANGVisitor::visitOrCond(BIFANGParser::OrCondContext *ctx) {
    hasLogicCond = true;

    string rCondBlkName = "lCondFalse";
    auto* rCondBlock = new BasicBlock(rCondBlkName, curFunc);

    BasicBlock* myTBlock = TBlock;
    BasicBlock* myFBlock = FBlock;
    FBlock = rCondBlock;

    //cerr <<"visitCond0: "<<ctx->cond(0)->getText()<<endl;

    isExpCond = false;
    any lCondRes = BIFANGVisitor::visit(ctx->cond(0));
    if (isExpCond) {
        auto* lCondVal = any_cast<ValueRef*>(lCondRes);
        ValueRef* lCondBool = BuildCmp(builder, lCondVal, zero, NE);
        BuildCondBr(builder, lCondBool, myTBlock, rCondBlock);
    }

    //cerr<<"cond0 visited"<<endl;

    //rCond
    curFunc->appendBlock(rCondBlock);
    builder->PositionBuilderAtEnd(rCondBlock);

    //cerr << "visitCond1: "<<ctx->cond(1)->getText()<<endl;

    FBlock = myFBlock;
    isExpCond = false;
    any rCondRes = BIFANGVisitor::visit(ctx->cond(1));
    if (isExpCond) {
        FBlock = rCondBlock;
        auto* rCondVal = any_cast<ValueRef*>(rCondRes);
        ValueRef* rCondBool = BuildCmp(builder, rCondVal, zero, NE);
        BuildCondBr(builder, rCondBool, myTBlock, myFBlock);
    }

    //cerr<<"cond1 visited"<<endl;

    isExpCond = false;
    return nullptr;
}
//cond: exp
std::any BIFANGVisitor::visitExpCond(BIFANGParser::ExpCondContext *ctx) {
    isExpCond = true;
    return BIFANGVisitor::visit(ctx->exp());
}
//cond: cond AND cond
std::any BIFANGVisitor::visitAndCond(BIFANGParser::AndCondContext *ctx) {
    //    //cerr<<"visitAndCond"<<endl;
    hasLogicCond = true;

    string rCondBlkName = "lCondTrue";
    auto* rCondBlock = new BasicBlock(rCondBlkName, curFunc);

    BasicBlock* myTBlock = TBlock;
    BasicBlock* myFBlock = FBlock;
    TBlock = rCondBlock;

    //cerr <<"visitCond0: "<<ctx->cond(0)->getText()<<endl;

    isExpCond = false;
    any lCondRes = BIFANGVisitor::visit(ctx->cond(0));
    if (isExpCond) {
        auto* lCondVal = any_cast<ValueRef*>(lCondRes);
        ValueRef* lCondBool = BuildCmp(builder, lCondVal, zero, NE);
        BuildCondBr(builder, lCondBool, rCondBlock, myFBlock);
    }
    //cerr<<"Cond0 visited"<<endl;

    //rCond
    curFunc->appendBlock(rCondBlock);
    builder->PositionBuilderAtEnd(rCondBlock);

    //cerr <<"visitCond1: "<<ctx->cond(1)->getText()<<endl;

    TBlock = myTBlock;
    isExpCond = false;
    any rCondRes = BIFANGVisitor::visit(ctx->cond(1));
    if (isExpCond) {
        auto* rCondVal = any_cast<ValueRef*>(rCondRes);
        ValueRef* rCondBool = BuildCmp(builder, rCondVal, zero, NE);
        BuildCondBr(builder, rCondBool, myTBlock, myFBlock);
    }

    //cerr<<"Cond1 visited"<<endl;

    isExpCond = false;
    return nullptr;
}
//cond: cond (EQ | NEQ) cond
std::any BIFANGVisitor::visitEqCond(BIFANGParser::EqCondContext *ctx) {
    //cerr<<"visitEqCond"<<endl;
    auto* lhs = any_cast<ValueRef*>(BIFANGVisitor::visit(ctx->cond(0)));
    auto* rhs = any_cast<ValueRef*>(BIFANGVisitor::visit(ctx->cond(1)));

    if (ctx->EQ() != nullptr)
        return BuildCmp(builder, lhs, rhs,EQ);
    else if (ctx->NEQ() != nullptr)
        return BuildCmp(builder, lhs, rhs,NE);
    else {
        cerr << "you should not arrive here!"<<endl;
        return nullptr;
    }
}
//lVal: IDENT (L_BRACKT exp R_BRACKT)*;
std::any BIFANGVisitor::visitLVal(BIFANGParser::LValContext *ctx) {
    string varName = ctx->IDENT()->getText();
    if (varName.length() > 31) varName = varName.substr(0, 5) + "_";
    Symbol * symbol = curScope->getVar(varName);

    if (ctx->exp().empty()) {
        return symbol;
    } else {
        if (symbol->symbolType->type == POINTERTYPE) {
            vector<ValueRef*> indices;
            for(int i = 0; i < ctx->exp().size(); ++i) {
                auto* idx = any_cast<ValueRef*>(BIFANGVisitor::visit(ctx->exp(i)));
                indices.push_back(idx);
            }
            ValueRef* varPtr = BuildLoad(builder, symbol);
            return BuildGEP(builder, varPtr, indices);

        } else { //symbol->symbolType->type == ARRAYTYPE
            vector<ValueRef*> indices;
            for(int i = 0; i < ctx->exp().size(); ++i) {
                auto* idx = any_cast<ValueRef*>(BIFANGVisitor::visit(ctx->exp(i)));
                indices.push_back(idx);
            }
            return BuildGEP(builder, symbol, indices);
        }
    }
}
//number: FLOAT_CONST | INTEGER_CONST ;
std::any BIFANGVisitor::visitNumber(BIFANGParser::NumberContext *ctx) {
    return BIFANGParserBaseVisitor::visitNumber(ctx);
}
//unaryOp: PLUS | MINUS | NOT;
std::any BIFANGVisitor::visitUnaryOp(BIFANGParser::UnaryOpContext *ctx) {
    return BIFANGParserBaseVisitor::visitUnaryOp(ctx);
}
//funcRParams: param (COMMA param)*;
std::any BIFANGVisitor::visitFuncRParams(BIFANGParser::FuncRParamsContext *ctx) {
    return BIFANGParserBaseVisitor::visitFuncRParams(ctx);
}
//param: exp;
std::any BIFANGVisitor::visitParam(BIFANGParser::ParamContext *ctx) {
    return BIFANGParserBaseVisitor::visitParam(ctx);
}
//constExp: exp;
std::any BIFANGVisitor::visitConstExp(BIFANGParser::ConstExpContext *ctx) {
    return BIFANGParserBaseVisitor::visitConstExp(ctx);
}

std::any BIFANGVisitor::getArrInitVal(Type* type,BIFANGParser::ConstInitValContext* ctx){
    if(ctx->constExp() != nullptr){
        if(type->type == INT32TYPE){
            return BuildFPTrunc(builder, any_cast<ValueRef *>(this->visit(ctx)));
        }
        else if(type->type == FLOATTYPE){
            return BuildSitofp(builder, any_cast<ValueRef *>(this->visit(ctx)));
        }
        cerr << "can't get here" << endl;
        throw exception();
    }

    // 本层为数组
    std::vector<std::any> v;
    Type* eleType = ((ArrayType*)type)->elementType;
    auto ctxs = ctx->constInitVal();
    for(int i=0;i<ctxs.size();i++){
        if(ctxs[i]->constExp() == nullptr){ //表明下一层还是个数组
            v.push_back(getArrInitVal(eleType,ctxs[i]));
        }
        else{ //下一层是个数字，此时要判断是不是省略括号的情况
            if(eleType->type != ARRAYTYPE) { // 正常到达数组最后一层
                v.push_back(getArrInitVal(eleType,ctxs[i]));
            }
            else{ // 省略括号情况
                v.emplace_back(GiveMeAnArray(ctxs,i,(ArrayType*)eleType));
            }
        }
    }
    return v;
}

std::any BIFANGVisitor::getArrInitVal(Type* type, BIFANGParser::InitValContext* ctx){
    if(ctx->exp() != nullptr){
        if(type->type == INT32TYPE){
            return BuildFPTrunc(builder, any_cast<ValueRef *>(this->visit(ctx)));
        }
        else if(type->type == FLOATTYPE){
            return BuildSitofp(builder, any_cast<ValueRef *>(this->visit(ctx)));
        }
        cerr << "can't get here" << endl;
        throw exception();
    }

    // 本层为数组
    std::vector<std::any> v;
    Type* eleType = ((ArrayType*)type)->elementType;
    auto ctxs = ctx->initVal();
    for(int i=0;i<ctxs.size();){
        if(ctxs[i]->exp() == nullptr){ //表明下一层还是个数组
            v.push_back(getArrInitVal(eleType,ctxs[i++]));
        }
        else{ //下一层是个数字，此时要判断是不是省略括号的情况
            if(eleType->type != ARRAYTYPE) { // 正常到达数组最后一层
                v.push_back(getArrInitVal(eleType,ctxs[i++]));
            }
            else{ // 省略括号情况
                v.emplace_back(GiveMeAnArray(ctxs,i,(ArrayType*)eleType));
            }
        }
    }
    return v;
}

vector<any> BIFANGVisitor::GiveMeAnArray(vector<BIFANGParser::ConstInitValContext*>& vals,int& idx,ArrayType* arr){
    Type * eleType = arr->elementType;
    vector<any> v;
    if(eleType->type == ARRAYTYPE){
        for(int i=0;i<arr->ele_cnt;i++){
            if(idx >= vals.size()) break;
            if(vals[idx]->constExp() != nullptr) //下一个元素为数字，应为省略括号
                v.emplace_back(GiveMeAnArray(vals,idx,(ArrayType*)eleType));
            else
                v.emplace_back(getArrInitVal(eleType,vals[idx++]));
        }
    }
    else{
        for(int i=0;i<arr->ele_cnt;i++){
            if(idx >= vals.size()) break;
            auto ctx = vals[idx];
            assert(ctx->constExp() != nullptr);

            if(ctx->constExp() != nullptr){
                if(eleType->type == INT32TYPE){
                    v.emplace_back(BuildFPTrunc(builder, any_cast<ValueRef *>(this->visit(ctx))));
                }
                else if(eleType->type == FLOATTYPE){
                    v.emplace_back(BuildSitofp(builder, any_cast<ValueRef *>(this->visit(ctx))));
                }
                else {
                    cerr << "can't get here" << endl;
                    throw exception();
                }
            }
            idx ++;
        }
    }
    return v;
}

vector<any> BIFANGVisitor::GiveMeAnArray(vector<BIFANGParser::InitValContext *> &vals, int &idx, ArrayType *arr) {
    Type * eleType = arr->elementType;
    vector<any> v;
    if(eleType->type == ARRAYTYPE){
        for(int i=0;i<arr->ele_cnt;i++){
            if(idx >= vals.size()) break;
            if(vals[idx]->exp() != nullptr) //下一个元素为数字，应为省略括号
                v.emplace_back(GiveMeAnArray(vals,idx,(ArrayType*)eleType));
            else
                v.emplace_back(getArrInitVal(eleType,vals[idx++]));
        }
    }
    else{
        for(int i=0;i<arr->ele_cnt;i++){
            if(idx >= vals.size()) break;
            auto ctx = vals[idx];
            assert(ctx->exp() != nullptr);

            if(ctx->exp() != nullptr){
                if(eleType->type == INT32TYPE){
                    v.emplace_back(BuildFPTrunc(builder, any_cast<ValueRef *>(this->visit(ctx))));
                }
                else if(eleType->type == FLOATTYPE){
                    v.emplace_back(BuildSitofp(builder, any_cast<ValueRef *>(this->visit(ctx))));
                }
                else {
                    cerr << "can't get here" << endl;
                    throw exception();
                }
            }
            idx ++;
        }
    }
    return v;
}




