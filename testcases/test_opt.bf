// test_opt.bf
int main() {
    // 1. 测试常量传播与折叠 (Constant Propagation)
    int a = 10;
    int b = 20;
    int c = a + b + 5; // 预期优化：编译器直接计算出 c = 35

    // 2. 测试代数化简 (Algebraic Simplification)
    int d = c + 0;     // 预期优化：+0 被消除，d 直接等于 c (即 35)
    int e = d * 1;     // 预期优化：*1 被消除

    // 3. 测试死代码消除 (Dead Code Elimination)
    int f = 100;       // 预期优化：f 从未被使用，这行指令应被完全删除
    int g = a * b;     // 预期优化：g 虽有计算但未被使用，应被删除

    // 4. 测试控制流简化 (CFG Simplification)
    int result = 0;
    if (1) {           // 预期优化：条件已知为真，分支判断指令应被删除
        result = e;    // 直接跳转或顺序执行到这里
    } else {
        result = 999;  // 预期优化：这块代码永远不可达，应被删除
    }

    return result;     // 最终应返回 35
}