// testcase_custom.bf
// 预期运行结果(echo $?): 55

int g_val = 10;
const int g_step = 2;

// 辅助函数：计算 x 的 n 倍
int multiply_helper(int x, int n) {
    int res = 0;
    int i = 0;
    while (i < n) {
        res = res + x;
        i = i + 1;
    }
    return res;
}

int main() {
    int a = 5;
    int b = 20;
    int arr[5]; // 测试数组分配
    
    // 初始化数组
    arr[0] = 1;
    arr[1] = 2;

    // 算术与逻辑运算测试
    // a = 5, g_val = 10 -> sum = 15
    int sum = a + g_val; 

    // 控制流测试 (If-Else)
    if (sum > 20) {
        sum = sum - 5;
    } else {
        // sum = 15 + 20 = 35
        sum = sum + b; 
    }

    // 循环与数组测试 (While)
    // 此时 sum = 35
    int k = 0;
    while (k < 3) {
        // 循环3次，每次减去 g_step (2)
        // 35 - 2 - 2 - 2 = 29
        sum = sum - g_step;
        k = k + 1;
    }

    // 函数调用测试
    // multiply_helper(5, 4) 应该返回 20
    int mul_res = multiply_helper(a, 4);

    // 综合计算
    // result = 29 + 20 + 1 + 5 = 55
    int final_res = sum + mul_res + arr[0] + 5;

    return final_res;
}