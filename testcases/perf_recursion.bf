// 测试点: 深度递归调用 (指数级复杂度)
// 目标: 计算 Fib(30)
// 预期结果: 832040 (注意: QEMU 返回值可能截断为 8 位，建议用 echo $? 查看时注意，或者只看运行时间)

int fib(int n) {
    if (n < 2) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

int main() {
    int n = 35; // 30 的计算量已经很大了，大约需要运行几百万次函数调用
    return fib(n);
}
