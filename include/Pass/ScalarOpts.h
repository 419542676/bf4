#ifndef COMPILER_SCALAROPTS_H
#define COMPILER_SCALAROPTS_H

#include "GlobalUnit.h"
#include "Function.h"
#include "BasicBlock.h"
#include "IRInstruction.h"
#include <vector>

class ScalarOpts {
public:
    GlobalUnit* globalUnit;
    bool changed; // 标记优化是否发生了改变

    ScalarOpts(GlobalUnit* gu) : globalUnit(gu), changed(false) {}

    // 1. 常量传播与折叠 (Constant Propagation & Folding)
    // 能够计算 1+2=3, 3*4=12 等
    void runConstantPropagation();

    // 2. 代数化简 (Algebraic Simplification)
    // 能够优化 x+0=x, x*1=x, x*0=0 等
    void runAlgebraicSimplification();

    // 3. 简单的死代码消除 (Simple Dead Code Elimination)
    // 移除计算结果未被使用的无副作用指令
    void runDeadCodeElimination();

    // 4. 控制流简化 (CFG Simplification)
    // 将条件确定的 CondBr 转换为 Br
    void runCFGSimplification();
    void runStoreLoadForwarding();

private:
    // 辅助函数：尝试计算两个常量的二元运算
    ValueRef* computeBinary(binaryType op, ValueRef* v1, ValueRef* v2);
    // 辅助函数：尝试计算两个常量的比较运算
    ValueRef* computeCmp(cmpType op, ValueRef* v1, ValueRef* v2);
};

#endif