// 测试点: 数组访问、三重循环
// 目标: 20x20 矩阵乘法
// 注意: 这里使用一维数组模拟二维，测试编译器对偏移量的计算优化

int A[400]; // 20 * 20
int B[400];
int C[400];

int main() {
    int N = 20;
    int i = 0;
    int j = 0;
    int k = 0;

    // 1. 初始化数组
    while (i < N * N) {
        A[i] = i % 10;
        B[i] = i % 5;
        i = i + 1;
    }

    // 2. 矩阵乘法 C = A * B
    // C[i][j] += A[i][k] * B[k][j]
    i = 0;
    while (i < N) {
        j = 0;
        while (j < N) {
            int sum = 0;
            k = 0;
            while (k < N) {
                // A[i*N + k] * B[k*N + j]
                int idxA = i * N + k;
                int idxB = k * N + j;
                sum = sum + A[idxA] * B[idxB];
                k = k + 1;
            }
            int idxC = i * N + j;
            C[idxC] = sum;
            j = j + 1;
        }
        i = i + 1;
    }

    // 返回 C[10][10] 的值作为一个校验码
    // idx = 10*20 + 10 = 210
    return C[210]; 
}
