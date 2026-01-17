#ifndef COMPILER_DOMNODE_H
#define COMPILER_DOMNODE_H

#include <vector>
#include "BasicBlock.h"

class DomNode {
public:
    BasicBlock *bb;
    
    // 支配树上的直接父节点 (Immediate Dominator)
    DomNode *IDOM = nullptr;
    
    // 支配树上的子节点 (用于遍历支配树)
    std::vector<DomNode*> children;
    
    // 支配边界 (Dominance Frontier) - Mem2Reg 必须用这个
    std::vector<DomNode*> DF;
    
    // 深度 (用于计算最近公共祖先)
    int depth = 0;

    // [修改点] 这里去掉函数体 {} 和冒号初始化，只保留分号 ;
    // 实现已经在 src/Pass/DomNode.cpp 中写好了
    explicit DomNode(BasicBlock *bb);
};

#endif
