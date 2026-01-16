#include "GlobalUnit.h"
#ifndef COMPILER_MEM2REGPASS_H
#define COMPILER_MEM2REGPASS_H


class Mem2RegPass {
public:
    GlobalUnit * globalUnit;

    explicit Mem2RegPass(GlobalUnit * gu){ this->globalUnit = gu; }

    void run();

    void insertPhi(Function * func);

    void renamePhi(DomNode * root);

    void mergeEntry(Function * func);
};


#endif