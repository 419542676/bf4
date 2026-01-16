// 寄存器压力测试
// 考察：当活跃变量超过物理寄存器数量时，Spill 处理是否正确
int main() {
    int a = 1; int b = 2; int c = 3; int d = 4; int e = 5;
    int f = 6; int g = 7; int h = 8; int i = 9; int j = 10;
    int k = 11; int l = 12; int m = 13; int n = 14; int o = 15;
    
    // 进行一轮复杂的混合运算，确保上述变量在此期间都是"活跃"的
    int sum = 0;
    int x = 0;
    while (x < 10000000) {
        // 这一长串运算迫使编译器必须保留所有变量的值
        sum = (a + b) * c + (d + e) * f + (g + h) * i + (j + k) * l + (m + n) * o;
        // 稍微修改其中几个，防止被死代码消除
        a = a + 1;
        b = b + 1;
        // 这里的取模是为了防止溢出变成负数，保持运算稳定
        a = a % 3;
        b = b % 3;
        x = x + 1;
    }
    
    // 随便返回一个依赖计算结果的值
    if (sum > 0) return 1;
    return 0;
}
