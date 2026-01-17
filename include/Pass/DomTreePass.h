#ifndef COMPILER_DOMTREEPASS_H
#define COMPILER_DOMTREEPASS_H

#include "GlobalUnit.h"
#include "DomNode.h"
#include <vector>
#include <map>
#include <set>

class DomTreePass {
private:
    GlobalUnit *globalUnit;

    // 内部辅助数据结构
    std::vector<BasicBlock*> postOrder; // 后序遍历序列
    std::vector<BasicBlock*> reversePostOrder; // 逆后序序列 (RPO)
    std::map<BasicBlock*, int> bb2int; // 基本块 -> RPO 索引映射

    // 辅助函数
    void computePostOrder(BasicBlock *bb, std::set<BasicBlock*> &visited);
    void calcIDoms(Function *func);
    void calcDF(Function *func);
    
    // 计算两个节点的最近公共支配者 (Least Common Ancestor)
    BasicBlock* intersect(BasicBlock* b1, BasicBlock* b2);

public:
    explicit DomTreePass(GlobalUnit *gu) : globalUnit(gu) {}
    
    // 入口函数
    void run();
    
};

#endif