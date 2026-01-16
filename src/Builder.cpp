#include "Builder.h"
using namespace std;

BasicBlock * Builder::AppendBasicBlock(Function *func, std::string& blockName) {
    BasicBlock * block = new BasicBlock(blockName,func);
    func->block_list.push_back(block);
    return block;
}

void Builder::PositionBuilderAtEnd(BasicBlock *block) {
    this->nowBlock = block;
}
//根据当前的代码块情况，将指令添加到全局块或当前函数的入口块或当前块中。
// 如果指令是ALLOCA类型的，则添加到当前函数的入口块中；否则，添加到当前块中。
void Builder::AppendCode(IRInstruction* instruction) {
    if(this->nowBlock == nullptr){ // 说明在全局块
        this->globalUnit->addInstr(instruction);
    }
    else{ //否则加到对应块内
        //如果是ALLOCA类型，则把指令插入在entry块中
        if(instruction->instType == ALLOCA){
            this->curFunc->entry->appendCode(instruction);
        }
        else {
            this->nowBlock->appendCode(instruction);
        }
    }
    instruction->block = nowBlock;
}

void Builder::LinkBlock(BasicBlock *succ) {
    // nowBlock ----> succ;
    this->nowBlock->succ.push_back(succ);
    succ->pred.push_back(this->nowBlock);
}


