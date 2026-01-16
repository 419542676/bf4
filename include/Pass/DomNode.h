#include "BasicBlock.h"
#include <vector>
#ifndef COMPILER_DOMNODE_H
#define COMPILER_DOMNODE_H

class DomNode {
public:
    int nodeId;
    BasicBlock * bb;

    std::vector<DomNode*> DOM; // 支配父节点
    std::vector<DomNode*> child; // 支配子节点
    DomNode* IDOM; //该节点在支配树中的父节点
    std::vector<DomNode*> DF; //该节点的支配前集

    int depth;

    DomNode(int id,BasicBlock * block);

    bool dominate(DomNode * d){
        return std::find(DOM.begin(), DOM.end(),d) != DOM.end();
    }
};


#endif
