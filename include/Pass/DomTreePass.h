#include "GlobalUnit.h"
#include "DomNode.h"
#ifndef COMPILER_DOMTREEPASS_H
#define COMPILER_DOMTREEPASS_H


class DomTreePass{
public:
    GlobalUnit* globalUnit;

    DomTreePass(GlobalUnit* gu){
        this->globalUnit = gu;
    }

    void run();

    DomNode *Gen_Dom_Tree(BasicBlock *entry);
};


#endif
