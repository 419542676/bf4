// BIFANG Test Case: Final Verification
// 目标: 验证 Mem2Reg, SSA, LICM, DCE, CFG Simplification

int main() {
    int sum = 0;
    int i = 0;
    int N = 10;
    int M = 20;

    // [测试点 1]: CFG 简化与死代码消除 (DCE)
    // cond 是常量 1，编译器应识别出 else 分支不可达并删除之。
    // Mem2Reg 应该能正确处理这里的控制流，不会在 merge 点产生错误的 Phi。
    int cond = 1; 
    int base = 0;
    if (cond) {
        base = 100;
    } else {
        base = 999; // Dead Code: 这个块应该被彻底删除
    }

    // [测试点 2]: 循环不变量外提 (LICM) 与 SSA
    // 循环运行 10 次
    while (i < N) {
        // [LICM]: invariant 只依赖 N 和 M (它们是循环不变的)
        // 优化器应将其移到循环的前置块 (PreHeader) 中，避免每次迭代都计算乘法。
        int invariant = N * M; // = 200
        
        // [DCE]: dead_val 计算后从未被使用，ScalarOpts 应将其删除
        int dead_val = invariant * 2; 

        // [SSA/Phi]: sum 在循环中累加，依赖上一次迭代的值 (Phi 节点)
        sum = sum + invariant; 
        
        // [SSA/Phi]: 内部控制流，测试 Mem2Reg 在循环内的 Phi 插入能力
        if (i < 5) {
            sum = sum + 1;
        } else {
            sum = sum + 2;
        }
        
        i = i + 1;
    }
    
    // 预期计算逻辑:
    // base = 100
    // Loop (0-9):
    // invariant = 200
    // i=0~4 (5次): sum += 200 + 1 = 201 * 5 = 1005
    // i=5~9 (5次): sum += 200 + 2 = 202 * 5 = 1010
    // total sum = 2015
    // result = 100 + 2015 = 2115

    return (base + sum) - 2100;
}