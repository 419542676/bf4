// BIFANG Test Case: Recursion & Globals
// 目标: 验证栈帧深度生长、RA保存恢复、全局变量读写

int g_offset = 20; // 全局变量，测试数据段访问

// 递归函数：计算阶乘
// 深度使用栈空间，如果溢出处理有问题，这里会崩溃
int factorial(int n) {
    if (n < 2) {
        return 1;
    }
    // 递归调用，需要保存 n 和返回地址
    return n * factorial(n - 1);
}

int main() {
    int sum = 0;
    int i = 0;
    int loop_limit = 5;

    // 1. 简单的循环测试 (Mem2Reg 和 Phi 验证)
    while (i < loop_limit) {
        sum = sum + i;
        i = i + 1;
    }
    // sum 应该是 0 + 1 + 2 + 3 + 4 = 10

    // 2. 递归调用测试 (Stack Frame 验证)
    // factorial(5) = 5 * 4 * 3 * 2 * 1 = 120
    int fact_res = factorial(5);

    // 3. 综合计算
    // 结果 = 10 (sum) + 120 (fact) + 20 (global) = 150
    return sum + fact_res + g_offset;
}