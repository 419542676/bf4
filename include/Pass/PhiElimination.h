#ifndef COMPILER_PHIELIMINATION_H
#define COMPILER_PHIELIMINATION_H

#include "GlobalUnit.h"


class PhiElimination {
private:
    GlobalUnit *globalUnit;
    void runOnFunction(Function* func);

public:
    explicit PhiElimination(GlobalUnit *gu) : globalUnit(gu) {}
    void run();
};

#endif