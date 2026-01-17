#include "Pass/DomTreePass.h"
#include <algorithm>
#include <stack>

using namespace std;

void DomTreePass::run() {
    for (auto &[name, func] : globalUnit->func_table) {
        if (func->block_list.empty()) continue;

        // 1. 清理旧的 DomNode 信息，防止污染
        // 假设 BasicBlock 有一个指向 DomNode 的指针 domNode (根据你原代码推测)
        // 或者是 func->dom_root
        // 这里我们重新创建 DomNode
        for (auto bb : func->block_list) {
            // 如果你之前手动 new 了 DomNode，这里最好 delete 掉，防止内存泄漏
            // 但为了安全起见，我们假设直接覆盖指针
            if (bb->domNode) {
                // delete bb->domNode; // 根据你的内存管理策略决定是否取消注释
                bb->domNode = nullptr;
            }
            bb->domNode = new DomNode(bb);
        }

        // 2. 计算后序和逆后序
        postOrder.clear();
        reversePostOrder.clear();
        bb2int.clear();
        
        set<BasicBlock*> visited;
        computePostOrder(func->entry, visited);
        
        // 生成 RPO (Reverse Post Order)
        reversePostOrder = postOrder;
        std::reverse(reversePostOrder.begin(), reversePostOrder.end());

        // 建立索引映射，方便快速比较先后关系
        for (int i = 0; i < reversePostOrder.size(); i++) {
            bb2int[reversePostOrder[i]] = i;
        }

        // 3. 计算直接支配者 (IDom)
        calcIDoms(func);

        // 4. 计算支配边界 (Dominance Frontier)
        calcDF(func);

        // 5. 设置根节点 (为了兼容你原来的代码接口)
        func->dom_root = func->entry->domNode;
    }
}

// 辅助：计算后序遍历
void DomTreePass::computePostOrder(BasicBlock *bb, set<BasicBlock*> &visited) {
    visited.insert(bb);
    for (auto succ : bb->succ) {
        if (visited.find(succ) == visited.end()) {
            computePostOrder(succ, visited);
        }
    }
    postOrder.push_back(bb);
}

// 核心算法：计算 IDom
void DomTreePass::calcIDoms(Function *func) {
    BasicBlock *entry = func->entry;
    
    // 初始化：Entry 的 IDom 是它自己（或空，取决于定义，Cooper算法中通常设为自己方便计算）
    entry->domNode->IDOM = entry->domNode;

    bool changed = true;
    while (changed) {
        changed = false;
        
        // 按逆后序遍历所有节点（跳过 Entry）
        for (auto bb : reversePostOrder) {
            if (bb == entry) continue;

            BasicBlock *newIdom = nullptr;
            
            // 找到第一个已经计算出 IDom 的前驱
            for (auto pred : bb->pred) {
                if (bb2int.count(pred) && pred->domNode->IDOM != nullptr) {
                    if (newIdom == nullptr) {
                        newIdom = pred;
                    } else {
                        newIdom = intersect(pred, newIdom);
                    }
                }
            }

            // 更新 IDom
            if (bb->domNode->IDOM != newIdom->domNode) {
                bb->domNode->IDOM = newIdom->domNode;
                changed = true;
            }
        }
    }
    
    // 修正：Entry 的 IDom 应该置空，或者保持自环，根据你后续代码习惯。
    // 标准树结构中根节点父节点为空。
    entry->domNode->IDOM = nullptr;

    // 构建 DomNode 的 children 关系（构建树）
    for (auto bb : reversePostOrder) {
        if (bb == entry) continue;
        if (bb->domNode->IDOM) {
            bb->domNode->IDOM->children.push_back(bb->domNode);
        }
    }
}

// 辅助：寻找两个节点的最近公共支配者
BasicBlock* DomTreePass::intersect(BasicBlock* b1, BasicBlock* b2) {
    // 只要两个节点不相等
    while (b1 != b2) {
        // 利用 RPO 索引比较先后关系
        // 注意：在 RPO 中，支配者通常索引较小
        // Cooper 算法要求：索引大的往上爬
        while (bb2int[b1] > bb2int[b2]) {
            b1 = b1->domNode->IDOM->bb;
        }
        while (bb2int[b2] > bb2int[b1]) {
            b2 = b2->domNode->IDOM->bb;
        }
    }
    return b1;
}

// 核心算法：计算支配边界 DF
// 既然我们有了 IDom 树，计算 DF 就很简单了
void DomTreePass::calcDF(Function *func) {
    for (auto bb : reversePostOrder) {
        // 如果一个节点有多个前驱，它就是汇合点，可能是某些节点的 DF
        if (bb->pred.size() >= 2) {
            for (auto pred : bb->pred) {
                BasicBlock *runner = pred;
                // 只要 runner 不是 bb 的直接支配者，就一直往上跑
                while (runner != bb->domNode->IDOM->bb) {
                    runner->domNode->DF.push_back(bb->domNode);
                    runner = runner->domNode->IDOM->bb;
                }
            }
        }
    }
}
