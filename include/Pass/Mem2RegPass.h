#ifndef COMPILER_MEM2REGPASS_H
#define COMPILER_MEM2REGPASS_H

#include "GlobalUnit.h"
#include "Pass/DomTreePass.h"
#include "IRInstruction.h"
#include <map>
#include <vector>
#include <stack>
#include <set>

class Mem2RegPass {
private:
    GlobalUnit *globalUnit;

    // [修复] 必须在这里声明这些私有函数，否则cpp文件中无法实现
    void insertPhi(Function *func);
    void renamePhi(DomNode *root);
    void mergeEntry(Function *func);

public:
    explicit Mem2RegPass(GlobalUnit *gu) : globalUnit(gu) {}

    void run();
};

#endif

