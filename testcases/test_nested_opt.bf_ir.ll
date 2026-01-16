define i32 @main() {
mainStart1:            ;No predecessor!!    succs:mainEntry2,
  %retVal3 = alloca i32, align 4
  %sum4 = alloca i32, align 4
  %i5 = alloca i32, align 4
  %N6 = alloca i32, align 4
  %M7 = alloca i32, align 4
  %j12 = alloca i32, align 4
  %inner_inv17 = alloca i32, align 4
  br label %mainEntry2
mainEntry2:            ;preds: mainStart1,    succs:whileCond8,
  store i32 0, i32* %retVal3, align 4
  store i32 0, i32* %sum4, align 4
  store i32 0, i32* %i5, align 4
  store i32 10, i32* %N6, align 4
  store i32 20, i32* %M7, align 4
  br label %whileCond8
whileCond8:            ;preds: mainEntry2,    succs:doWhileBody9,whileNext11,
  %0 = load i32, i32* %i5, align 4
  %1 = icmp slt i32 %0, 5
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %doWhileBody9, label %whileNext11
doWhileBody9:            ;preds: whileCond8,doWhileCond10,    succs:whileCond13,
  store i32 0, i32* %j12, align 4
  br label %whileCond13
whileCond13:            ;preds: doWhileBody9,    succs:loop_preheader_020,whileNext16,
  %4 = load i32, i32* %j12, align 4
  %5 = icmp slt i32 %4, 5
  %6 = zext i1 %5 to i32
  %7 = icmp ne i32 %6, 0
  br i1 %7, label %loop_preheader_020, label %whileNext16
loop_preheader_020:            ;preds: whileCond13,    succs:doWhileBody14,
  %8 = load i32, i32* %N6, align 4
  %9 = load i32, i32* %M7, align 4
  %10 = add i32 %8, %9
  br label %doWhileBody14
doWhileBody14:            ;preds: doWhileCond15,loop_preheader_020,    succs:doWhileCond15,
  store i32 %10, i32* %inner_inv17, align 4
  %11 = load i32, i32* %sum4, align 4
  %13 = add i32 %11, %10
  store i32 %13, i32* %sum4, align 4
  %14 = load i32, i32* %j12, align 4
  %15 = add i32 %14, 1
  store i32 %15, i32* %j12, align 4
  br label %doWhileCond15
doWhileCond15:            ;preds: doWhileBody14,    succs:doWhileBody14,whileNext16,
  %16 = load i32, i32* %j12, align 4
  %17 = icmp slt i32 %16, 5
  %18 = zext i1 %17 to i32
  %19 = icmp ne i32 %18, 0
  br i1 %19, label %doWhileBody14, label %whileNext16
whileNext16:            ;preds: whileCond13,doWhileCond15,    succs:doWhileCond10,
  %20 = load i32, i32* %i5, align 4
  %21 = add i32 %20, 1
  store i32 %21, i32* %i5, align 4
  br label %doWhileCond10
doWhileCond10:            ;preds: whileNext16,    succs:doWhileBody9,whileNext11,
  %22 = load i32, i32* %i5, align 4
  %23 = icmp slt i32 %22, 5
  %24 = zext i1 %23 to i32
  %25 = icmp ne i32 %24, 0
  br i1 %25, label %doWhileBody9, label %whileNext11
whileNext11:            ;preds: whileCond8,doWhileCond10,    succs:if.end19,
  br label %if.end19
if.end19:            ;preds: whileNext11,    succs:mainRet0,
  %26 = load i32, i32* %sum4, align 4
  store i32 %26, i32* %retVal3, align 4
  br label %mainRet0
mainRet0:            ;preds: if.end19,    succs:
  %27 = load i32, i32* %retVal3, align 4
  ret i32 %27
}
