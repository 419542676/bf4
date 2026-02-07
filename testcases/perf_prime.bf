// 测试点: 纯计算、双层循环、大量分支
// 目标: 计算 1 到 3000 之间的素数个数
// 预期结果: 3000以内素数个数为 430

int is_prime(int n) {
    if (n < 2) return 0;
    int i = 2;
    // 简单的试除法，故意没用 sqrt 以增加计算量
    while (i * i <= n) {
        if (n % i == 0) return 0;
        i = i + 1;
    }
    return 1;
}

int main() {
    int sum = 0;
    int i = 0;
    while (i < 50000) {
        if (is_prime(i)) {
            sum = sum + 1;
        }
        i = i + 1;
    }
    return sum; // 应该是 430
}
