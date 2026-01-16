#ifndef LOOP_OPTS_H
#define LOOP_OPTS_H

#include "GlobalUnit.h"
#include "Pass/DomTreePass.h" 
#include <vector>
#include <set>
#include <algorithm>
#include <string> 

// 定义简单的自然循环结构
struct Loop {
    BasicBlock* header;             // 循环头 (被回边指向的块)
    std::set<BasicBlock*> blocks;   // 循环体内的所有块
    BasicBlock* preHeader;          // 循环前置块 (用于存放外提代码)

    Loop(BasicBlock* h) : header(h), preHeader(nullptr) {
        blocks.insert(h);
    }
};

class LoopOpts {
private:
    GlobalUnit* globalUnit;
    DomTreePass* domTreePass; 
    bool changed;

    // 1. 识别自然循环
    std::vector<Loop*> findLoops(Function* func);
    
    // 2. 查找循环不变指令
    std::vector<Instruction*> findInvariants(Loop* loop);
    
    // 3. 代码外提
    void hoistInstructions(Loop* loop, const std::vector<Instruction*>& invariants, Function* func);

    // 辅助：检查值是否在循环外定义
    bool isDefinedOutside(ValueRef* val, Loop* loop);

    // 辅助：创建 PreHeader
    BasicBlock* createPreHeader(Loop* loop, Function* func);
    
    // 辅助：获取修改过的指针
    std::set<ValueRef*> getModifiedPointers(Loop* loop);
    
    // 辅助：调试日志 (只声明，实现在 .cpp 文件中)
    void debugLog(const std::string& msg); 

public:
    // 必须要有构造函数，否则 IROptimizer 无法创建它
    LoopOpts(GlobalUnit* gu, DomTreePass* dt) : globalUnit(gu), domTreePass(dt), changed(false) {}
    
    void Run();
};

#endif