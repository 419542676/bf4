#ifndef COMPILER_IRInstruction_H
#define COMPILER_IRInstruction_H

#include <exception>
#include "BasicBlock.h"
#include "ValueRef.h"
#include "Function.h"
#include "Instruction.h"
#include "Backend/AsmBuilder.hpp"
#include "Backend/MachineInstruction.hpp"
#include "Backend/MachineOperand.hpp"

using namespace std;

enum binaryType {ADD, SUB, MUL, DIV, MOD, AND, OR};
enum cmpType {EQ, NE, LT, LE, GT, GE};


class IRInstruction : public Instruction{
public:

    BasicBlock* block; // 所属基本块,nullptr表示全局指令
    static int vRegCount;//虚拟寄存器计数器
    static int vfRegCount;//虚拟浮点寄存器计数器
    static int labelCount; // 标签计数器
    static std::map<std::string, double> float_table; //name:floatconst

    explicit IRInstruction(InstType_Enum instType);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override {}
    //设置虚拟寄存器数量
    static void setVRegisterCount(int n){
        vRegCount = n;
    }
    //获得最后一个已使用的虚拟寄存器
    static std::string getLastVRegister(int pre = 1){
        return "VREG" + std::to_string(vRegCount - pre);
    }
    //获得一个新的虚拟寄存器
    static std::string getVRegister(){
        return "VREG" + std::to_string(vRegCount++);
    }
    //获取最后一个已经使用的浮点虚拟寄存器
    static std::string getLastFVRegister(int pre = 1){
        return "FVREG" + std::to_string(vfRegCount - pre);
    }
    //获取一个新的浮点虚拟寄存器
    static std::string getFVRegister(){
        return "FVREG" + std::to_string(vfRegCount++);
    }
    //获取最后一个已经使用的标签
    static std::string getLC(int pre = 1){
        return ".LC" + std::to_string( labelCount - pre);
    }
    //生成一个新的标签
    static std::string generateLC(){
        return ".LC" + std::to_string( labelCount++);
    }
    /*函数返回，恢复帧指针和返回地址
    第一种：先恢复寄存器，再释放栈空间
    foo:
        addi sp, sp, -16   # 分配栈空间
        sd ra, 8(sp)       # 保存返回地址
        sd fp, 0(sp)       # 保存旧的帧指针
        addi fp, sp, 16    # 设置新的帧指针

        # 函数foo的操作...
        # 可以使用帧指针(fp)来访问局部变量和参数

        ld ra, 8(sp)       # 恢复返回地址
        ld fp, 0(sp)       # 恢复旧的帧指针
        addi sp, sp, 16    # 释放栈空间
        ret                # 返回调用

    第二种：先释放栈空间，再恢复寄存器
        addi sp, sp, -(16+offset)
        sd ra, (offset+8)(sp)
        sd fp, offset(sp)
        addi fp, sp, 16+offset

        # 函数foo的操作...
        # 可以使用帧指针(fp)来访问局部变量和参数

        addi sp, sp, offset+16
        ld ra, -8(sp)
        ld fp, -16(sp)
        ret             */
    //这里采用第二种
    static void retFunc(AsmBuilder *pBuilder, int offset){
        auto cur_block = pBuilder->getBlock();
        int framesize = offset + 16;
        auto addi = new BinaryMInstruction(cur_block,
                                           BinaryMInstruction::ADDI,
                                           new MachineOperand(MachineOperand::REG, IREGISTER::SP),
                                           new MachineOperand(MachineOperand::REG, IREGISTER::SP),
                                           new MachineOperand(MachineOperand::IMM, offset+16));
        cur_block->insertInst(addi);
        //从栈底开始的16个字节用来存储函数的返回地址和FP的值
        //创建一个 LD 指令，将返回地址（RA 寄存器）加载到寄存器中。返回地址在栈上的偏移为 -8
        auto ld1 = new LoadMInstruction(cur_block,
                                        LoadMInstruction::LD,
                                        new MachineOperand(MachineOperand::REG, IREGISTER::RA),
                                        new MachineOperand(MachineOperand::IMM, -8), // framesize - 8
                                        new MachineOperand(MachineOperand::REG, IREGISTER::SP));
        cur_block->insertInst(ld1);
        //创建一个 LD 指令，将帧指针（FP 寄存器）加载到寄存器中。帧指针在栈上的偏移为 -16
        auto ld2 = new LoadMInstruction(cur_block,
                                        LoadMInstruction::LD,
                                        new MachineOperand(MachineOperand::REG, IREGISTER::FP),
                                        new MachineOperand(MachineOperand::IMM, -16), // framesize
                                        new MachineOperand(MachineOperand::REG, IREGISTER::SP));
        cur_block->insertInst(ld2);
        //创建一个 JR 指令，用于跳转到返回地址（RA 寄存器）所指示的位置
        auto jr = new JrMInstruction(cur_block,
                                     JrMInstruction::JR,
                                     new MachineOperand(MachineOperand::REG, IREGISTER::RA));
        cur_block->insertInst(jr);
    }
    //li VREG2, IMM
    static void loadImmIntoReg(AsmBuilder *pBuilder, long value){
        auto cur_block = pBuilder->getBlock();
        auto liImm = new LoadImmInstruction(cur_block,
                                            LoadImmInstruction::LI,
                                            new MachineOperand(MachineOperand::VREG, getVRegister()),
                                            new MachineOperand(MachineOperand::IMM, value));
        pBuilder->getBlock()->insertInst(liImm);
    }

//    将布尔值取反  xori t0, a1, 1
    static void xoriReg(AsmBuilder *pBuilder, MachineOperand* t){
        auto cur_block = pBuilder->getBlock();
        auto xori = new BinaryMInstruction(cur_block,
                                           BinaryMInstruction::XORI,
                                           t,
                                           new MachineOperand(*t),
                                           new MachineOperand(MachineOperand::IMM, 1));
        pBuilder->getBlock()->insertInst(xori);
    }

//    binary   op dst, src1, src2
    static void BinaryInstr(AsmBuilder *pBuilder, BinaryMInstruction::OpType op, string dst, string src1, string src2, bool isfloat = false){
        auto cur_block = pBuilder->getBlock();
        auto bin = new BinaryMInstruction(cur_block,
                                          op,
                                          new MachineOperand(MachineOperand::VREG, dst),
                                          new MachineOperand(MachineOperand::VREG, src1),
                                          new MachineOperand(MachineOperand::VREG, src2));
        pBuilder->getBlock()->insertInst(bin);
    }

//    add register and imm
//    addi指令编码中 imm占12位表示范围-2048~2047   addi VREG2, VREG2, 800
//    如果超出addi指令规定的imm表示范围，则需要保存到寄存器中改用add指令  add VREG2, VREG2, VREG3
    static void Addiw(AsmBuilder *pBuilder, BinaryMInstruction::OpType op, string dst, string src1, int imm){
        auto cur_block = pBuilder->getBlock();
        if(op != BinaryMInstruction::ADDI){
            throw new NotImplemented("unexpected optype in function Addiw");
        }
        else{
            if(abs(imm) > 2000){
                loadImmIntoReg(pBuilder, imm);
                auto bin = new BinaryMInstruction(cur_block,
                                                  BinaryMInstruction::ADD,
                                                  new MachineOperand(MachineOperand::VREG, dst),
                                                  new MachineOperand(MachineOperand::VREG, src1),
                                                  new MachineOperand(MachineOperand::VREG, getLastVRegister()));
                pBuilder->getBlock()->insertInst(bin);
            }else{
                auto bin = new BinaryMInstruction(cur_block,
                                                  op,
                                                  new MachineOperand(MachineOperand::VREG, dst),
                                                  new MachineOperand(MachineOperand::VREG, src1),
                                                  new MachineOperand(MachineOperand::IMM, imm));
                pBuilder->getBlock()->insertInst(bin);
            }
        }
    }

//    f bin
    static void fBinaryInstr(AsmBuilder *pBuilder, BinaryMInstruction::OpType op, string dst, string src1, string src2){
        auto cur_block = pBuilder->getBlock();
        auto fbin = new BinaryMInstruction(cur_block,
                                          op,
                                          new MachineOperand(MachineOperand::FVREG, dst),
                                          new MachineOperand(MachineOperand::FVREG, src1),
                                          new MachineOperand(MachineOperand::FVREG, src2));
        pBuilder->getBlock()->insertInst(fbin);
    }

//    jump label    j label
    static void JumpLabel(AsmBuilder *pBuilder, const string& label){
        auto br = new JumpMInstruction(pBuilder->getBlock(),
                                       JumpMInstruction::J,
                                       new MachineOperand(MachineOperand::LABEL, label));
        pBuilder->getBlock()->insertInst(br);
    }

//    load label  LA VREG2, label  伪指令,实际转换车auipc和addi指令完成加载
    static void LoadLabel(AsmBuilder *pBuilder, const string &vreg, const string& label){
        auto la = new LoadImmInstruction(pBuilder->getBlock(),
                                         LoadImmInstruction::LA,
                                         new MachineOperand(MachineOperand::VREG, vreg),
                                         new MachineOperand(MachineOperand::LABEL, label));
        pBuilder->getBlock()->insertInst(la);
    }

//    load float   flw FVREG2, 0(x10)  加载某个地址的值到浮点寄存器中
    static void LoadFloat(AsmBuilder *pBuilder, const string &fvreg, const string& vreg){
        auto flw = new LoadMInstruction(pBuilder->getBlock(),
                                        LoadMInstruction::FLW,
                                        new MachineOperand(MachineOperand::FVREG, fvreg),
                                        new MachineOperand(MachineOperand::IMM, 0),
                                        new MachineOperand(MachineOperand::VREG, vreg));
        pBuilder->getBlock()->insertInst(flw);
    }

//    static float cmp  两个浮点寄存器中的值进行比较  fcmp.gt VREG2, FVREG3, FVREG4
    static void FCmp(AsmBuilder *pBuilder, CmpMInstruction::OpType op, const string &result, const string& fvreg1, const string& fvreg2){
        auto fcmp = new CmpMInstruction(pBuilder->getBlock(),
                                       op,
                                       new MachineOperand(MachineOperand::VREG, result),
                                       new MachineOperand(MachineOperand::FVREG, fvreg1),
                                       new MachineOperand(MachineOperand::FVREG, fvreg2));
        pBuilder->getBlock()->insertInst(fcmp);
    }
    //从FP一定偏移量的地址处读取值，如果偏移量属于-2048~2047(这里简化成绝对值小于2000)，
    // 则用 ld VREG, imm(fp)  否则先把offset装入寄存器
    static void loadFromFP(AsmBuilder *pBuilder,LoadMInstruction::OpType optype, string dst, int imm){
        if (abs(imm) < 2000) {
            auto lw1 = new LoadMInstruction(pBuilder->getBlock(),
                                        optype,
                                        new MachineOperand(MachineOperand::VREG, dst),
                                        new MachineOperand(MachineOperand::IMM, imm),
                                        new MachineOperand(MachineOperand::REG, IREGISTER::FP));
            pBuilder->getBlock()->insertInst(lw1);
        } else {
            //把offset加载到寄存器
            loadImmIntoReg(pBuilder, imm);
            //把offset和fp想加得到地址存入寄存器
            auto add = new BinaryMInstruction(pBuilder->getBlock(), BinaryMInstruction::ADD,
                                                new MachineOperand(MachineOperand::VREG, getLastVRegister()),
                                                new MachineOperand(MachineOperand::VREG, getLastVRegister()),
                                                new MachineOperand(MachineOperand::REG, IREGISTER::FP));
            pBuilder->getBlock()->insertInst(add);
            //加载对应地址处的值到寄存器
            auto lw = new LoadMInstruction(pBuilder->getBlock(), optype,
                                                new MachineOperand(MachineOperand::VREG, dst),
                                                new MachineOperand(MachineOperand::IMM, 0),
                                                new MachineOperand(MachineOperand::VREG, getLastVRegister()));
            pBuilder->getBlock()->insertInst(lw);
        }
    }
    //浮点数版本
    static void loadFloatFromFP(AsmBuilder *pBuilder,LoadMInstruction::OpType optype, string dst, int imm){
        if (abs(imm) < 2000) {
            auto lw1 = new LoadMInstruction(pBuilder->getBlock(),
                                        optype,
                                        new MachineOperand(MachineOperand::FVREG, dst),
                                        new MachineOperand(MachineOperand::IMM, imm),
                                        new MachineOperand(MachineOperand::REG, IREGISTER::FP));
            pBuilder->getBlock()->insertInst(lw1);
        } else {
            loadImmIntoReg(pBuilder, imm);
            auto add = new BinaryMInstruction(pBuilder->getBlock(), BinaryMInstruction::ADD,
                                                new MachineOperand(MachineOperand::VREG, getLastVRegister()),
                                                new MachineOperand(MachineOperand::VREG, getLastVRegister()),
                                                new MachineOperand(MachineOperand::REG, IREGISTER::FP));
            pBuilder->getBlock()->insertInst(add);
            auto lw = new LoadMInstruction(pBuilder->getBlock(), optype,
                                                new MachineOperand(MachineOperand::FVREG, dst),
                                                new MachineOperand(MachineOperand::IMM, 0),
                                                new MachineOperand(MachineOperand::VREG, getLastVRegister()));
            pBuilder->getBlock()->insertInst(lw);
        }
    }
    //sd VREG2, imm(fp)  将VREG2的值存到 imm(fp)地址处
    static void storeToStack(AsmBuilder *pBuilder, StoreMInstruction::OpType optype, std::string src, int imm) {
        if (abs(imm) < 2032) {
            auto store = new StoreMInstruction(pBuilder->getBlock(), optype,
                                                new MachineOperand(MachineOperand::VREG, src),
                                                new MachineOperand(MachineOperand::IMM, imm),
                                                new MachineOperand(MachineOperand::REG, IREGISTER::FP));
            pBuilder->getBlock()->insertInst(store);
        } else {
            //超出范围，先把offset加载进寄存器
            loadImmIntoReg(pBuilder, imm);
            //把offset和fp想加，得到目标地址存入寄存器
            auto add = new BinaryMInstruction(pBuilder->getBlock(), BinaryMInstruction::ADD,
                                                new MachineOperand(MachineOperand::VREG, getLastVRegister()),
                                                new MachineOperand(MachineOperand::VREG, getLastVRegister()),
                                                new MachineOperand(MachineOperand::REG, IREGISTER::FP));
            pBuilder->getBlock()->insertInst(add);
            //sd VREG2, 0(VREG3)
            auto store = new StoreMInstruction(pBuilder->getBlock(), optype,
                                                new MachineOperand(MachineOperand::VREG, src),
                                                new MachineOperand(MachineOperand::IMM, 0),
                                                new MachineOperand(MachineOperand::VREG, getLastVRegister()));
            pBuilder->getBlock()->insertInst(store);
        }
    }
    //浮点数版本
    static void storeFloatToStack(AsmBuilder *pBuilder, StoreMInstruction::OpType optype, std::string src, int imm) {
        if (abs(imm) < 2032) {
            auto store = new StoreMInstruction(pBuilder->getBlock(), optype,
                                                new MachineOperand(MachineOperand::FVREG, src),
                                                new MachineOperand(MachineOperand::IMM, imm),
                                                new MachineOperand(MachineOperand::REG, IREGISTER::FP));
            pBuilder->getBlock()->insertInst(store);
        } else {
            loadImmIntoReg(pBuilder, imm);
            auto add = new BinaryMInstruction(pBuilder->getBlock(), BinaryMInstruction::ADD,
                                                new MachineOperand(MachineOperand::VREG, getLastVRegister()),
                                                new MachineOperand(MachineOperand::VREG, getLastVRegister()),
                                                new MachineOperand(MachineOperand::REG, IREGISTER::FP));
            pBuilder->getBlock()->insertInst(add);
            auto store = new StoreMInstruction(pBuilder->getBlock(), optype,
                                                new MachineOperand(MachineOperand::FVREG, src),
                                                new MachineOperand(MachineOperand::IMM, 0),
                                                new MachineOperand(MachineOperand::VREG, getLastVRegister()));
            pBuilder->getBlock()->insertInst(store);
        }
    }
//    arr  初始化整型数组
    static void arrInitInt(std::vector<std::any> values, ArrayType* arrayType, std::stringstream &ss){
        int sizeTotal = arrayType->size;
        //values为空，生成一个大小为sizeTotal的全零数组
        if(values.empty()){
            ss << "\t.zero\t" << sizeTotal << '\n';
            return;
        }
        //一维数组
        if(values.at(0).type() != typeid(vector<any>)){
            for(auto & value : values){
                ss << "\t.word\t" << any_cast<ValueRef*>(value)->get_Ref() << endl;
                sizeTotal -= 4;
            }

            if(sizeTotal > 0)
                ss << "\t.zero\t" << sizeTotal << '\n';
        }
        //多维数组,递归调用arrInitInt函数来处理嵌套数组
        else{
            int sum = 0;
            for(auto & value : values){
                sum += (dynamic_cast<ArrayType*>(arrayType->elementType))->size;
                arrInitInt(any_cast<vector<any>>(value), dynamic_cast<ArrayType*>(arrayType->elementType) ,ss);
            }
            if(sum < sizeTotal){
                ss << "\t.zero\t" << sizeTotal-sum << '\n';
            }
        }
    }
    //浮点数版本
    static void arrInitFloat(std::vector<std::any> values, ArrayType* arrayType, std::stringstream &ss){
        int sizeTotal = arrayType->size;
        if(values.empty()){
            ss << "\t.zero\t" << sizeTotal << '\n';
            return;
        }
        if(values.at(0).type() != typeid(vector<any>)){
// one dimension
            for(auto & value : values){
//                TODO: warning : cast type from double to float
                float val = ((Float_Const*)any_cast<ValueRef*>(value))->value;
                unsigned long dec = float2dec(val);
                if(val < 0){
                    ss << "\t.word\t-" << dec << endl;
                }else{
                    ss << "\t.word\t" << dec << endl;
                }
                sizeTotal -= 4;
            }

            if(sizeTotal > 0)
                ss << "\t.zero\t" << sizeTotal << '\n';
        }
        else{
            for(auto & value : values){
                arrInitFloat(any_cast<vector<any>>(value), dynamic_cast<ArrayType*>(arrayType->elementType) ,ss);
            }
        }
    }

    //float
    //将单精度浮点数转换为十进制表示的无符号长整型
    static unsigned long float2dec(float f){
//        float f = stof(value);
        std::bitset<32> bits(*reinterpret_cast<unsigned int*>(&f));
        //把bits转换为无符号长整型
        unsigned long decimal_value = static_cast<int>(bits.to_ulong());
        //若浮点数f是负数，则将其转换为补码形式，即对其二进制表示取反加一
        if (f < 0) {
            decimal_value = ~(decimal_value - 1);
        }
        return decimal_value;
    }

    //float
    //将浮点数常量存储到名为 float_table 的数组
    static void isFloatConst(ValueRef* value){
        float_table[generateLC()] = ((Float_Const*)value)->value;
    }
};

class DummyInstruction : public IRInstruction {//NOP指令
public:

    DummyInstruction();

    //void outPut(std::ostream &os) override;
};

class AddGlobalInstruction : public IRInstruction {
public:
    ValueRef* dst;
    Type* varType;
    ValueRef* initVal;
    string debugInfo;

    AddGlobalInstruction(ValueRef* dst, Type* varType, ValueRef* initVal, string& debugInfo);

    void codegen(AsmBuilder *pBuilder) const;

    void outPut(std::ostream &os) override { os << debugInfo << endl; }

    void replace(ValueRef *old, ValueRef *now) override;
};

class AllocaInstruction : public IRInstruction {
public:
    ValueRef* dst;
    Type* varType;
    string debugInfo;

    AllocaInstruction(ValueRef* dst, Type* varType, string& debugInfo);

    void outPut(std::ostream &os) override { os << debugInfo << endl; }

    void replace(ValueRef *old, ValueRef *now) override;
};

class LoadInstruction : public IRInstruction {
public:
    ValueRef* dst;
    ValueRef* src;

    LoadInstruction(ValueRef* dst,ValueRef* src);//(ValueRef* dst, Pointer* src)?

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;
    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class StoreInstruction : public IRInstruction {
public:
    ValueRef* dst;
    ValueRef* src;

    StoreInstruction(ValueRef* dst,ValueRef* src);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};
class BinaryInstruction : public IRInstruction {
public:

    ValueRef* dst;
    ValueRef* src1;
    ValueRef* src2;
    binaryType opTy;

    BinaryInstruction(ValueRef* dst,ValueRef* src1, ValueRef* src2, binaryType opTy);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class CmpInstruction : public IRInstruction {
public:
    ValueRef* result;
    ValueRef* src1;
    ValueRef* src2;
    cmpType opTy;

    CmpInstruction(ValueRef* result, ValueRef* src1, ValueRef* src2, cmpType opTy);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class BrInstruction : public IRInstruction {
public:
    BasicBlock* label;

    BrInstruction(BasicBlock* label);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class CondBrInstruction : public IRInstruction {
public:
    ValueRef* condition;
    BasicBlock* trueLabel;
    BasicBlock* falseLabel;

    CondBrInstruction(ValueRef* condition, BasicBlock* trueLabel, BasicBlock* falseLabel);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class RetInstruction : public IRInstruction {
public:
    ValueRef* retVal; // nullptr 表示 ret void;

    RetInstruction(ValueRef* retVal);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;
    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class CallInstruction : public IRInstruction {
public:
    ValueRef* retVal;
    Function* function;
    vector<ValueRef*> args;

    CallInstruction(ValueRef* retVal, Function* function, vector<ValueRef*>& args);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class ZExtInstruction : public IRInstruction {
public:
    ValueRef* dst;
    ValueRef* src;

    ZExtInstruction(ValueRef* dst,ValueRef* src);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class XorInstruction : public IRInstruction {
public:
    // 理论上只有Xor true的情况，所以另一个参数永远为1(i1/i32)
    ValueRef* dst;
    ValueRef* src;

    XorInstruction(ValueRef* dst, ValueRef* src);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;


    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class GEPInstruction : public IRInstruction {
public:
    ValueRef* dst;
    ValueRef* src;
    ValueRef* index; // 暂时做成只取一层下标的

    GEPInstruction(ValueRef* dst, ValueRef* src, ValueRef* index);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class PhiInstruction : public IRInstruction {
public:
    ValueRef* symbol; // you shouldn't use this
    ValueRef* result;
    int branch_cnt;
    map<BasicBlock*, ValueRef*> mp;

    PhiInstruction(ValueRef* symbol,ValueRef* result,int cnt);
    
    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override
    {
        throw exception();
    }

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class FPTIInstruction : public IRInstruction {
public:
    ValueRef* dst;
    ValueRef* src;

    FPTIInstruction(ValueRef* dst, ValueRef* src);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class ITFPInstruction : public IRInstruction {
public:
    ValueRef* dst;
    ValueRef* src;

    ITFPInstruction(ValueRef* dst, ValueRef* src);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class FNegInstruction : public IRInstruction {
public:
    ValueRef* dst;
    ValueRef* src;

    FNegInstruction(ValueRef* dst, ValueRef* src);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old, ValueRef *now) override;
};

class MemsetInstruction : public IRInstruction{
public:
    ValueRef * start; // 数组首地址(但不保证是arr型)
    int len;
    int byte; // 要填充的内容,8bit

    MemsetInstruction(ValueRef * start, int len, int byte);

    void outPut(std::ostream &os) override;

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void replace(ValueRef *old,ValueRef *now) override;
};

class MoveInstruction : public IRInstruction{
public:
    ValueRef* src;
    ValueRef* dst;

    MoveInstruction(ValueRef* dst, ValueRef* src);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old,ValueRef *now) override;
};

class SllInstruction : public IRInstruction {
public:
    ValueRef* src1;
    ValueRef* bits; // 移动多少位
    ValueRef* dst;

    SllInstruction(ValueRef* dst, ValueRef* src1, ValueRef* bits);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old,ValueRef *now) override;
};

class SraInstruction : public IRInstruction {
public:
    ValueRef* src1;
    ValueRef* bits; // 移动多少位
    ValueRef* dst;

    SraInstruction(ValueRef* dst, ValueRef* src1, ValueRef* bits);

    void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) override;

    void outPut(std::ostream &os) override;

    void replace(ValueRef *old,ValueRef *now) override;
};
#endif

