int main() {
    // [优化目标 1] 常量传播 (Constant Propagation)
    // 编译器应该能推导出 const_a = 100, const_b = 200
    int const_a = 100;
    int const_b = 200;

    // [优化目标 2] 控制流简化 (CFG Simplification)
    // 1 > 0 永远为真，"else" 分支不仅永远不会执行，连生成的代码块都应该被彻底删除
    int cond_val = 0;
    if (1 > 0) {
        cond_val = 10;
    } else {
        cond_val = 9999; // 这行代码对应的指令应该完全消失
    }

    // [优化目标 3] 代数化简 (Algebraic Simplification)
    // x + 0 等于 x，这条加法指令应该被消除
    cond_val = cond_val + 0;

    int i = 0;
    int sum = 0;

    // [优化目标 4] 循环不变式外提 (LICM)
    // (const_a + const_b) 的结果(300)每次循环都一样
    // 编译器应该把这次加法移到 while 循环外面（PreHeader）
    while (i < 10) {
        int invariant_calc = const_a + const_b;
        sum = sum + invariant_calc;
        i = i + 1;
    }

    // [优化目标 5] 死代码消除 (DCE)
    // dead_var 算出来后从未被使用（return 也没用到它）
    // 相关的乘法和存储指令应该被全部删除
    int dead_var = const_a * const_b;

    // 最终计算: sum(300 * 10) + cond_val(10) = 3010
    return sum + cond_val;
}