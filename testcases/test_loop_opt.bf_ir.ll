define i32 @main() {
mainStart1:            ;No predecessor!!    succs:mainEntry2,
  %retVal3 = alloca i32, align 4
  %i4 = alloca i32, align 4
  %sum5 = alloca i32, align 4
  %const_val_16 = alloca i32, align 4
  %const_val_27 = alloca i32, align 4
  %invariant_calc12 = alloca i32, align 4
  %simplify_val13 = alloca i32, align 4
  br label %mainEntry2
mainEntry2:            ;preds: mainStart1,    succs:whileCond8,
  store i32 0, i32* %retVal3, align 4
  store i32 0, i32* %i4, align 4
  store i32 0, i32* %sum5, align 4
  store i32 100, i32* %const_val_16, align 4
  store i32 200, i32* %const_val_27, align 4
  br label %whileCond8
whileCond8:            ;preds: mainEntry2,    succs:loop_preheader_015,whileNext11,
  %0 = load i32, i32* %i4, align 4
  %1 = icmp slt i32 %0, 10
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %loop_preheader_015, label %whileNext11
loop_preheader_015:            ;preds: whileCond8,    succs:doWhileBody9,
  %4 = load i32, i32* %const_val_16, align 4
  %5 = load i32, i32* %const_val_27, align 4
  %6 = add i32 %4, %5
  br label %doWhileBody9
doWhileBody9:            ;preds: doWhileCond10,loop_preheader_015,    succs:doWhileCond10,
  store i32 %6, i32* %invariant_calc12, align 4
  store i32 %6, i32* %simplify_val13, align 4
  %9 = load i32, i32* %sum5, align 4
  %11 = add i32 %9, %6
  store i32 %11, i32* %sum5, align 4
  %12 = load i32, i32* %i4, align 4
  %13 = add i32 %12, 1
  store i32 %13, i32* %i4, align 4
  br label %doWhileCond10
doWhileCond10:            ;preds: doWhileBody9,    succs:doWhileBody9,whileNext11,
  %14 = load i32, i32* %i4, align 4
  %15 = icmp slt i32 %14, 10
  %16 = zext i1 %15 to i32
  %17 = icmp ne i32 %16, 0
  br i1 %17, label %doWhileBody9, label %whileNext11
whileNext11:            ;preds: whileCond8,doWhileCond10,    succs:mainRet0,
  %18 = load i32, i32* %const_val_16, align 4
  %19 = load i32, i32* %const_val_27, align 4
  %20 = mul i32 %18, %19
  store i32 %20, i32* %dead_calc14, align 4
  %21 = load i32, i32* %sum5, align 4
  store i32 %21, i32* %retVal3, align 4
  br label %mainRet0
mainRet0:            ;preds: whileNext11,    succs:
  %22 = load i32, i32* %retVal3, align 4
  ret i32 %22
}
