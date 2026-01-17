#include "Pass/DomNode.h"

// 构造函数：初始化并建立 BasicBlock -> DomNode 的双向连接
DomNode::DomNode(BasicBlock *block) {
    this->bb = block;
    this->IDOM = nullptr;
    
    // 确保 BasicBlock 类中有 domNode 成员
    // (根据你之前的代码，BasicBlock 应该有一个 domNode 指针)
    block->domNode = this;
}
