@g_val = dso_local global i32 10, align 4
@g_step = dso_local global i32 2, align 4
define i32 @main() {
mainStart13:            ;No predecessor!!    succs:mainEntry14,
  %retVal15 = alloca i32, align 4
  %a16 = alloca i32, align 4
  %b17 = alloca i32, align 4
  %arr18 = alloca [5 x i32], align 16
  %sum19 = alloca i32, align 4
  %k23 = alloca i32, align 4
  %mul_res28 = alloca i32, align 4
  %final_res29 = alloca i32, align 4
  br label %mainEntry14
mainEntry14:            ;preds: mainStart13,    succs:if.then20,if.else21,
  store i32 0, i32* %retVal15, align 4
  store i32 5, i32* %a16, align 4
  store i32 20, i32* %b17, align 4
  %0 = getelementptr [5 x i32], [5 x i32]* %arr18, i32 0, i32 0
  store i32 1, i32* %0, align 4
  %1 = getelementptr [5 x i32], [5 x i32]* %arr18, i32 0, i32 1
  store i32 2, i32* %1, align 4
  %2 = load i32, i32* %a16, align 4
  %3 = load i32, i32* @g_val, align 4
  %4 = add i32 %2, %3
  store i32 %4, i32* %sum19, align 4
  %5 = load i32, i32* %sum19, align 4
  %6 = icmp slt i32 20, %5
  %7 = zext i1 %6 to i32
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %if.then20, label %if.else21
if.then20:            ;preds: mainEntry14,    succs:if.end22,
  %9 = load i32, i32* %sum19, align 4
  %10 = sub i32 %9, 5
  store i32 %10, i32* %sum19, align 4
  br label %if.end22
if.else21:            ;preds: mainEntry14,    succs:if.end22,
  %11 = load i32, i32* %sum19, align 4
  %12 = load i32, i32* %b17, align 4
  %13 = add i32 %11, %12
  store i32 %13, i32* %sum19, align 4
  br label %if.end22
if.end22:            ;preds: if.then20,if.else21,    succs:whileCond24,
  store i32 0, i32* %k23, align 4
  br label %whileCond24
whileCond24:            ;preds: if.end22,    succs:doWhileBody25,whileNext27,
  %14 = load i32, i32* %k23, align 4
  %15 = icmp slt i32 %14, 3
  %16 = zext i1 %15 to i32
  %17 = icmp ne i32 %16, 0
  br i1 %17, label %doWhileBody25, label %whileNext27
doWhileBody25:            ;preds: whileCond24,doWhileCond26,    succs:doWhileCond26,
  %18 = load i32, i32* %sum19, align 4
  %19 = sub i32 %18, 2
  store i32 %19, i32* %sum19, align 4
  %20 = load i32, i32* %k23, align 4
  %21 = add i32 %20, 1
  store i32 %21, i32* %k23, align 4
  br label %doWhileCond26
doWhileCond26:            ;preds: doWhileBody25,    succs:doWhileBody25,whileNext27,
  %22 = load i32, i32* %k23, align 4
  %23 = icmp slt i32 %22, 3
  %24 = zext i1 %23 to i32
  %25 = icmp ne i32 %24, 0
  br i1 %25, label %doWhileBody25, label %whileNext27
whileNext27:            ;preds: whileCond24,doWhileCond26,    succs:mainRet12,
  %26 = load i32, i32* %a16, align 4
  %27 = call i32 @multiply_helper(i32 %26,i32 4)
  store i32 %27, i32* %mul_res28, align 4
  %28 = load i32, i32* %sum19, align 4
  %29 = load i32, i32* %mul_res28, align 4
  %30 = add i32 %28, %29
  %31 = getelementptr [5 x i32], [5 x i32]* %arr18, i32 0, i32 0
  %32 = load i32, i32* %31, align 4
  %33 = add i32 %30, %32
  %34 = add i32 %33, 5
  store i32 %34, i32* %final_res29, align 4
  %35 = load i32, i32* %final_res29, align 4
  store i32 %35, i32* %retVal15, align 4
  br label %mainRet12
mainRet12:            ;preds: whileNext27,    succs:
  %36 = load i32, i32* %retVal15, align 4
  ret i32 %36
}
define i32 @multiply_helper(i32 %0, i32 %1) {
multiply_helperStart1:            ;No predecessor!!    succs:multiply_helperEntry2,
  %retVal3 = alloca i32, align 4
  %x4 = alloca i32, align 4
  %n5 = alloca i32, align 4
  %res6 = alloca i32, align 4
  %i7 = alloca i32, align 4
  br label %multiply_helperEntry2
multiply_helperEntry2:            ;preds: multiply_helperStart1,    succs:whileCond8,
  store i32 0, i32* %retVal3, align 4
  store i32 %0, i32* %x4, align 4
  store i32 %1, i32* %n5, align 4
  store i32 0, i32* %res6, align 4
  store i32 0, i32* %i7, align 4
  br label %whileCond8
whileCond8:            ;preds: multiply_helperEntry2,    succs:doWhileBody9,whileNext11,
  %2 = load i32, i32* %i7, align 4
  %3 = load i32, i32* %n5, align 4
  %4 = icmp slt i32 %2, %3
  %5 = zext i1 %4 to i32
  %6 = icmp ne i32 %5, 0
  br i1 %6, label %doWhileBody9, label %whileNext11
doWhileBody9:            ;preds: whileCond8,doWhileCond10,    succs:doWhileCond10,
  %7 = load i32, i32* %res6, align 4
  %8 = load i32, i32* %x4, align 4
  %9 = add i32 %7, %8
  store i32 %9, i32* %res6, align 4
  %10 = load i32, i32* %i7, align 4
  %11 = add i32 %10, 1
  store i32 %11, i32* %i7, align 4
  br label %doWhileCond10
doWhileCond10:            ;preds: doWhileBody9,    succs:doWhileBody9,whileNext11,
  %12 = load i32, i32* %i7, align 4
  %13 = load i32, i32* %n5, align 4
  %14 = icmp slt i32 %12, %13
  %15 = zext i1 %14 to i32
  %16 = icmp ne i32 %15, 0
  br i1 %16, label %doWhileBody9, label %whileNext11
whileNext11:            ;preds: whileCond8,doWhileCond10,    succs:multiply_helperRet0,
  %17 = load i32, i32* %res6, align 4
  store i32 %17, i32* %retVal3, align 4
  br label %multiply_helperRet0
multiply_helperRet0:            ;preds: whileNext11,    succs:
  %18 = load i32, i32* %retVal3, align 4
  ret i32 %18
}
