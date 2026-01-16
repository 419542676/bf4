// 作用域测试
// 考察：全局变量与局部变量同名时的处理
int a = 100;
int b = 200;

int func(int a) {
    // 这里的 a 是参数，掩盖了全局 a
    // 这里的 b 是全局 b
    return a + b;
}

int main() {
    int sum = 0;
    int i = 0;
    while (i < 1000000) {
        int b = 5; // 这里的 b 掩盖了全局 b
        // func(b) -> 传入 5
        // func 内部: return 5 + 200 (全局b) = 205
        // main 内部: sum += 205 + 100 (全局a) + 5 (局部b)
        sum = sum + func(b) + a + b;
        i = i + 1;
    }
    // 防止 sum 溢出，取个模
    return sum % 255;
}
