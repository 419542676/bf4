// test_loop_opt.bf
// 用于测试循环不变式外提 (LICM) 和标量优化

int main() {
    int i = 0;
    int sum = 0;
    
    // 外部定义变量，用于测试不变量识别
    int const_val_1 = 100;
    int const_val_2 = 200;

    // while 循环
    while (i < 10) {
        // [优化目标 1] 循环不变式外提 (LICM)
        // invariant_calc 的计算只依赖外部变量，每次循环结果都一样 (300)
        // 预期优化：这行计算指令 (ADD) 应该被移动到循环体外面 (PreHeader)
        int invariant_calc = const_val_1 + const_val_2;

        // [优化目标 2] 代数化简 + 标量传播
        // x + 0 应该直接化简为 x (即 invariant_calc)
        int simplify_val = invariant_calc + 0;

        // 这里的 sum 计算依赖循环变量，不能外提，但 simplify_val 应该是常量 300
        sum = sum + simplify_val;

        i = i + 1;
    }

    // [优化目标 3] 死代码消除 (DCE)
    // 下面这行代码计算了但没用，应该被删掉
    int dead_calc = const_val_1 * const_val_2;

    // 返回结果应该为 300 * 10 = 3000
    return sum;
}