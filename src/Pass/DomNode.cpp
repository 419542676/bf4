#include "Pass/DomNode.h"
#include <vector>
#include <map>
#include <stack>
#include <set>
using namespace std;


DomNode::DomNode(int id, BasicBlock *block) {
    this->nodeId = id;
    this->bb = block;
    this->IDOM = nullptr;
    block->domNode = this;
}



