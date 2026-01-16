@a = dso_local global i32 100, align 4
@b = dso_local global i32 200, align 4
define i32 @func(i32 %0) {
funcStart1:            ;No predecessor!!    succs:funcEntry2,
  %retVal3 = alloca i32, align 4
  %a4 = alloca i32, align 4
  br label %funcEntry2
funcEntry2:            ;preds: funcStart1,    succs:funcRet0,
  store i32 0, i32* %retVal3, align 4
  store i32 %0, i32* %a4, align 4
  %1 = load i32, i32* %a4, align 4
  %2 = load i32, i32* @b, align 4
  %3 = add i32 %1, %2
  store i32 %3, i32* %retVal3, align 4
  br label %funcRet0
funcRet0:            ;preds: funcEntry2,    succs:
  %4 = load i32, i32* %retVal3, align 4
  ret i32 %4
}
define i32 @main() {
mainStart6:            ;No predecessor!!    succs:mainEntry7,
  %retVal8 = alloca i32, align 4
  %sum9 = alloca i32, align 4
  %i10 = alloca i32, align 4
  %b15 = alloca i32, align 4
  br label %mainEntry7
mainEntry7:            ;preds: mainStart6,    succs:whileCond11,
  store i32 0, i32* %retVal8, align 4
  store i32 0, i32* %sum9, align 4
  store i32 0, i32* %i10, align 4
  br label %whileCond11
whileCond11:            ;preds: mainEntry7,    succs:doWhileBody12,whileNext14,
  %0 = load i32, i32* %i10, align 4
  %1 = icmp slt i32 %0, 1000000
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %doWhileBody12, label %whileNext14
doWhileBody12:            ;preds: whileCond11,doWhileCond13,    succs:doWhileCond13,
  store i32 5, i32* %b15, align 4
  %4 = load i32, i32* %sum9, align 4
  %5 = load i32, i32* %b15, align 4
  %6 = call i32 @func(i32 %5)
  %7 = add i32 %4, %6
  %8 = load i32, i32* @a, align 4
  %9 = add i32 %7, %8
  %10 = load i32, i32* %b15, align 4
  %11 = add i32 %9, %10
  store i32 %11, i32* %sum9, align 4
  %12 = load i32, i32* %i10, align 4
  %13 = add i32 %12, 1
  store i32 %13, i32* %i10, align 4
  br label %doWhileCond13
doWhileCond13:            ;preds: doWhileBody12,    succs:doWhileBody12,whileNext14,
  %14 = load i32, i32* %i10, align 4
  %15 = icmp slt i32 %14, 1000000
  %16 = zext i1 %15 to i32
  %17 = icmp ne i32 %16, 0
  br i1 %17, label %doWhileBody12, label %whileNext14
whileNext14:            ;preds: whileCond11,doWhileCond13,    succs:mainRet5,
  %18 = load i32, i32* %sum9, align 4
  %19 = srem i32 %18, 255
  store i32 %19, i32* %retVal8, align 4
  br label %mainRet5
mainRet5:            ;preds: whileNext14,    succs:
  %20 = load i32, i32* %retVal8, align 4
  ret i32 %20
}
