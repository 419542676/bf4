// 3n+1 猜想 (Collatz Conjecture)
// 考察：频繁的条件跳转和循环
int collatz(int n) {
    int step = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        step = step + 1;
    }
    return step;
}

int main() {
    // 计算 1 到 1000 所有数字的步数总和
    int i = 1;
    int total_steps = 0;
    while (i < 1000) {
        total_steps = total_steps + collatz(i);
        i = i + 1;
    }
    // 只是为了返回一个校验值
    return total_steps; 
}
