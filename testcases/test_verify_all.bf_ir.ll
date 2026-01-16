define i32 @main() {
mainStart1:            ;No predecessor!!    succs:mainEntry2,
  %retVal3 = alloca i32, align 4
  %const_a4 = alloca i32, align 4
  %const_b5 = alloca i32, align 4
  %cond_val6 = alloca i32, align 4
  %i10 = alloca i32, align 4
  %sum11 = alloca i32, align 4
  %invariant_calc16 = alloca i32, align 4
  br label %mainEntry2
mainEntry2:            ;preds: mainStart1,    succs:if.then7,
  store i32 0, i32* %retVal3, align 4
  store i32 100, i32* %const_a4, align 4
  store i32 200, i32* %const_b5, align 4
  store i32 0, i32* %cond_val6, align 4
  br label %if.then7
if.then7:            ;preds: mainEntry2,    succs:if.end9,
  store i32 10, i32* %cond_val6, align 4
  br label %if.end9
if.end9:            ;preds: if.then7,    succs:whileCond12,
  %0 = load i32, i32* %cond_val6, align 4
  store i32 %0, i32* %cond_val6, align 4
  store i32 0, i32* %i10, align 4
  store i32 0, i32* %sum11, align 4
  br label %whileCond12
whileCond12:            ;preds: if.end9,    succs:loop_preheader_018,whileNext15,
  %2 = load i32, i32* %i10, align 4
  %3 = icmp slt i32 %2, 10
  %4 = zext i1 %3 to i32
  %5 = icmp ne i32 %4, 0
  br i1 %5, label %loop_preheader_018, label %whileNext15
loop_preheader_018:            ;preds: whileCond12,    succs:doWhileBody13,
  %6 = load i32, i32* %const_a4, align 4
  %7 = load i32, i32* %const_b5, align 4
  %8 = add i32 %6, %7
  br label %doWhileBody13
doWhileBody13:            ;preds: doWhileCond14,loop_preheader_018,    succs:doWhileCond14,
  store i32 %8, i32* %invariant_calc16, align 4
  %9 = load i32, i32* %sum11, align 4
  %11 = add i32 %9, %8
  store i32 %11, i32* %sum11, align 4
  %12 = load i32, i32* %i10, align 4
  %13 = add i32 %12, 1
  store i32 %13, i32* %i10, align 4
  br label %doWhileCond14
doWhileCond14:            ;preds: doWhileBody13,    succs:doWhileBody13,whileNext15,
  %14 = load i32, i32* %i10, align 4
  %15 = icmp slt i32 %14, 10
  %16 = zext i1 %15 to i32
  %17 = icmp ne i32 %16, 0
  br i1 %17, label %doWhileBody13, label %whileNext15
whileNext15:            ;preds: whileCond12,doWhileCond14,    succs:mainRet0,
  %18 = load i32, i32* %const_a4, align 4
  %19 = load i32, i32* %const_b5, align 4
  %20 = mul i32 %18, %19
  store i32 %20, i32* %dead_var17, align 4
  %21 = load i32, i32* %sum11, align 4
  %22 = load i32, i32* %cond_val6, align 4
  %23 = add i32 %21, %22
  store i32 %23, i32* %retVal3, align 4
  br label %mainRet0
mainRet0:            ;preds: whileNext15,    succs:
  %24 = load i32, i32* %retVal3, align 4
  ret i32 %24
}
