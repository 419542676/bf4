int main() {
    int sum = 0;
    int i = 0;
    int N = 10;
    int M = 20;
    
    // [外层循环]
    while (i < 5) {
        int j = 0;
        
        // [内层循环]
        while (j < 5) {
            // 优化目标 1: 循环不变式外提 (LICM)
            // (N + M) 是 30，这个计算应该被提到内层循环外面
            // 甚至可能被提到外层循环外面（取决于优化强度，至少要出内层）
            int inner_inv = N + M;
            
            sum = sum + inner_inv;
            j = j + 1;
        }
        i = i + 1;
    }
    
    // 优化目标 2: 控制流简化 (CFG Simplification)
    // 0 不等于 1，这个 if 块及其内部代码应该被彻底删除
    if (0) {
        sum = -999;
    }
    
    // 预期结果: 
    // 外层跑5次，内层跑5次，总共25次
    // 每次加 (10+20)=30
    // sum = 25 * 30 = 750
    return sum;
}