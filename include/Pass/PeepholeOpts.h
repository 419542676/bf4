#ifndef BIFANG_PEEPHOLEOPTS_H
#define BIFANG_PEEPHOLEOPTS_H

#include "GlobalUnit.h"
#include "Pass/IROptimizer.h"

class PeepholeOpts {
private:
    GlobalUnit* globalUnit;
    void replaceAllUses(Function* func, ValueRef* oldVal, ValueRef* newVal);
    bool runOnFunction(Function* func);

public:
    PeepholeOpts(GlobalUnit* gu) : globalUnit(gu) {}
    void replaceAllUses(Function* func, ValueRef* oldVal, ValueRef* newVal, Instruction* exceptInst);
    void run();
};

#endif //BIFANG_PEEPHOLEOPTS_H