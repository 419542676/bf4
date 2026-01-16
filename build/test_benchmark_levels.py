import os
import subprocess
import time
import sys

# ================= 配置区域 =================
COMPILER_EXEC = "./BIFANG"
TESTCASES_DIR = "../testcases"
RISCV_PREFIX = "riscv64-linux-gnu-"
GCC_CMD = f"{RISCV_PREFIX}gcc"
SIZE_CMD = f"{RISCV_PREFIX}size"
QEMU_CMD = "qemu-riscv64"

# 优化等级列表
GCC_OPTS = ["-O0", "-O1", "-O2", "-O3"]

class Colors:
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    CYAN = '\033[96m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BOLD = '\033[1m'
    ENDC = '\033[0m'

def get_file_size(filepath):
    """获取 .text 段大小"""
    if not os.path.exists(filepath): return 0
    try:
        result = subprocess.run([SIZE_CMD, filepath], capture_output=True, text=True)
        lines = result.stdout.strip().split('\n')
        if len(lines) < 2: return 0
        return int(lines[1].split()[0]) # text size
    except:
        return 0

def run_cmd_timed(cmd_list):
    """运行命令并计时"""
    start = time.time()
    try:
        res = subprocess.run(cmd_list, capture_output=True, text=True)
        return res.returncode, time.time() - start
    except:
        return None, 0

def compile_gcc(src, out, opt_level):
    """GCC 编译"""
    cmd = [GCC_CMD, "-x", "c", opt_level, "-static", "-o", out, src]
    subprocess.run(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

def main():
    if not os.path.exists(TESTCASES_DIR):
        print("Testcases directory not found.")
        return

    files = sorted([f for f in os.listdir(TESTCASES_DIR) if f.endswith(".bf")])
    
    print(f"{Colors.HEADER}=== BIFANG Benchmark vs GCC Optimization Levels ==={Colors.ENDC}\n")

    for filename in files:
        filepath = os.path.join(TESTCASES_DIR, filename)
        asm_file = filepath + "_out.s"
        bif_exe = "bf_bench.out"
        
        # 打印当前测试文件标题
        print(f"{Colors.BOLD}>>> Test File: {filename}{Colors.ENDC}")
        
        # 表头
        print(f"  {'COMPILER':<12} | {'RESULT':<6} | {'TIME (s)':<10} | {'SIZE (B)':<8} | {'RATIO (Bif/Gcc)':<15}")
        print("  " + "-" * 65)

        # -------------------------------------------
        # 1. 运行 BIFANG (主角)
        # -------------------------------------------
        # 编译
        subprocess.run([COMPILER_EXEC, filepath], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        if os.path.exists(asm_file):
            subprocess.run([GCC_CMD, "-static", "-o", bif_exe, asm_file], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            bif_ret, bif_time = run_cmd_timed([QEMU_CMD, bif_exe])
            bif_size = get_file_size(bif_exe)
            bif_status = "OK" if bif_ret is not None else "ERR"
        else:
            bif_ret, bif_time, bif_size, bif_status = -999, 0, 0, "Fail"

        # 打印 BIFANG 数据
        print(f"  {Colors.CYAN}{'BIFANG':<12}{Colors.ENDC} | {bif_status:<6} | {bif_time:<10.6f} | {bif_size:<8} | {'(Baseline)':<15}")

        # -------------------------------------------
        # 2. 运行 GCC 各个等级 (对照组)
        # -------------------------------------------
        for opt in GCC_OPTS:
            gcc_exe = f"gcc_{opt[1:]}.out"
            compile_gcc(filepath, gcc_exe, opt)
            
            gcc_ret, gcc_time = run_cmd_timed([QEMU_CMD, gcc_exe])
            gcc_size = get_file_size(gcc_exe)
            
            # 结果校验
            if gcc_ret == bif_ret:
                res_str = f"{Colors.GREEN}PASS{Colors.ENDC}"
            else:
                res_str = f"{Colors.RED}FAIL{Colors.ENDC}"

            # 计算倍率 (BIFANG / GCC)
            if gcc_time > 0.0001:
                ratio = bif_time / gcc_time
                # 颜色区分：差距在 2 倍以内绿色，5 倍以内黄色，否则红色
                if ratio < 2.0: r_col = Colors.GREEN
                elif ratio < 5.0: r_col = Colors.YELLOW
                else: r_col = Colors.RED
                ratio_str = f"{r_col}{ratio:.2f}x{Colors.ENDC}"
            else:
                ratio_str = "-"

            print(f"  {'GCC '+opt:<12} | {res_str:<15} | {gcc_time:<10.6f} | {gcc_size:<8} | {ratio_str:<15}")
            
            if os.path.exists(gcc_exe): os.remove(gcc_exe)

        print("") # 空行分隔
        
        # 清理 BIFANG 临时文件
        if os.path.exists(bif_exe): os.remove(bif_exe)

if __name__ == "__main__":
    main()