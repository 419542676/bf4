// 计算 1 到 1000 万的累加和
int main() {
    int i = 0;
    int sum = 0;
    while (i < 10000000) {
        sum = sum + i;
        i = i + 1;
    }
    return sum;
}