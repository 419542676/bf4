// 递归计算斐波那契数列
// 考察：大量的函数调用指令 (call/ret) 和栈帧管理
int fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    // fib(30) 计算量较大，能明显看出性能差异
    // 预期结果：832040
    return fib(30);
}
