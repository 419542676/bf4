#include "GlobalUnit.h"
#include "DomNode.h"
#ifndef COMPILER_HOPTIMIZER_H
#define COMPILER_HOPTIMIZER_H


class IROptimizer {
public:
    GlobalUnit * globalUnit;

    IROptimizer(GlobalUnit * gu);
    void Optimize();

    void BuildCFG();

    void Constlize();

    void debug();
};


#endif
