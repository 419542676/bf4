#ifndef BIFANG_SCALAROPTS_H
#define BIFANG_SCALAROPTS_H

#include "GlobalUnit.h"
#include "Instruction.h"
#include "IRInstruction.h"
#include <vector>

class ScalarOpts {
private:
    GlobalUnit* globalUnit;

    // 辅助：判断指令是否有副作用
    bool hasSideEffects(Instruction* inst);

    // 辅助：从操作数的 use 链中移除当前指令
    void removeUseFromOperands(Instruction* inst);

    // 辅助：执行整数二元运算
    int computeInt(binaryType op, int v1, int v2);

    // 辅助：执行整数比较运算
    // [修改] 使用正确的 cmpType
    int computeCmp(cmpType op, int v1, int v2);

public:
    bool changed = false; 

    ScalarOpts(GlobalUnit* gu) : globalUnit(gu) {}

    // 1. 常量传播
    void runConstantPropagation();

    // 2. 代数化简
    void runAlgebraicSimplification();

    // 3. 死代码消除
    void runDeadCodeElimination();
    
    // 4. Store-Load 转发 (占位)
    void runStoreLoadForwarding();
    
    // 5. CFG 简化 (占位)
    void runCFGSimplification();
};

#endif //BIFANG_SCALAROPTS_H