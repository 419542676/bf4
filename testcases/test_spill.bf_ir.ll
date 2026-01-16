define i32 @main() {
mainStart1:            ;No predecessor!!    succs:mainEntry2,
  %retVal3 = alloca i32, align 4
  %a4 = alloca i32, align 4
  %b5 = alloca i32, align 4
  %c6 = alloca i32, align 4
  %d7 = alloca i32, align 4
  %e8 = alloca i32, align 4
  %f9 = alloca i32, align 4
  %g10 = alloca i32, align 4
  %h11 = alloca i32, align 4
  %i12 = alloca i32, align 4
  %j13 = alloca i32, align 4
  %k14 = alloca i32, align 4
  %l15 = alloca i32, align 4
  %m16 = alloca i32, align 4
  %n17 = alloca i32, align 4
  %o18 = alloca i32, align 4
  %sum19 = alloca i32, align 4
  %x20 = alloca i32, align 4
  br label %mainEntry2
mainEntry2:            ;preds: mainStart1,    succs:whileCond21,
  store i32 0, i32* %retVal3, align 4
  store i32 1, i32* %a4, align 4
  store i32 2, i32* %b5, align 4
  store i32 3, i32* %c6, align 4
  store i32 4, i32* %d7, align 4
  store i32 5, i32* %e8, align 4
  store i32 6, i32* %f9, align 4
  store i32 7, i32* %g10, align 4
  store i32 8, i32* %h11, align 4
  store i32 9, i32* %i12, align 4
  store i32 10, i32* %j13, align 4
  store i32 11, i32* %k14, align 4
  store i32 12, i32* %l15, align 4
  store i32 13, i32* %m16, align 4
  store i32 14, i32* %n17, align 4
  store i32 15, i32* %o18, align 4
  store i32 0, i32* %sum19, align 4
  store i32 0, i32* %x20, align 4
  br label %whileCond21
whileCond21:            ;preds: mainEntry2,    succs:doWhileBody22,whileNext24,
  %0 = load i32, i32* %x20, align 4
  %1 = icmp slt i32 %0, 10000000
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %doWhileBody22, label %whileNext24
doWhileBody22:            ;preds: whileCond21,doWhileCond23,    succs:doWhileCond23,
  %4 = load i32, i32* %a4, align 4
  %5 = load i32, i32* %b5, align 4
  %6 = add i32 %4, %5
  %7 = load i32, i32* %c6, align 4
  %8 = mul i32 %6, %7
  %9 = load i32, i32* %d7, align 4
  %10 = load i32, i32* %e8, align 4
  %11 = add i32 %9, %10
  %12 = load i32, i32* %f9, align 4
  %13 = mul i32 %11, %12
  %14 = add i32 %8, %13
  %15 = load i32, i32* %g10, align 4
  %16 = load i32, i32* %h11, align 4
  %17 = add i32 %15, %16
  %18 = load i32, i32* %i12, align 4
  %19 = mul i32 %17, %18
  %20 = add i32 %14, %19
  %21 = load i32, i32* %j13, align 4
  %22 = load i32, i32* %k14, align 4
  %23 = add i32 %21, %22
  %24 = load i32, i32* %l15, align 4
  %25 = mul i32 %23, %24
  %26 = add i32 %20, %25
  %27 = load i32, i32* %m16, align 4
  %28 = load i32, i32* %n17, align 4
  %29 = add i32 %27, %28
  %30 = load i32, i32* %o18, align 4
  %31 = mul i32 %29, %30
  %32 = add i32 %26, %31
  store i32 %32, i32* %sum19, align 4
  %33 = load i32, i32* %a4, align 4
  %34 = add i32 %33, 1
  store i32 %34, i32* %a4, align 4
  %35 = load i32, i32* %b5, align 4
  %36 = add i32 %35, 1
  store i32 %36, i32* %b5, align 4
  %37 = load i32, i32* %a4, align 4
  %38 = srem i32 %37, 3
  store i32 %38, i32* %a4, align 4
  %39 = load i32, i32* %b5, align 4
  %40 = srem i32 %39, 3
  store i32 %40, i32* %b5, align 4
  %41 = load i32, i32* %x20, align 4
  %42 = add i32 %41, 1
  store i32 %42, i32* %x20, align 4
  br label %doWhileCond23
doWhileCond23:            ;preds: doWhileBody22,    succs:doWhileBody22,whileNext24,
  %43 = load i32, i32* %x20, align 4
  %44 = icmp slt i32 %43, 10000000
  %45 = zext i1 %44 to i32
  %46 = icmp ne i32 %45, 0
  br i1 %46, label %doWhileBody22, label %whileNext24
whileNext24:            ;preds: whileCond21,doWhileCond23,    succs:if.then25,if.end26,
  %47 = load i32, i32* %sum19, align 4
  %48 = icmp slt i32 0, %47
  %49 = zext i1 %48 to i32
  %50 = icmp ne i32 %49, 0
  br i1 %50, label %if.then25, label %if.end26
if.then25:            ;preds: whileNext24,    succs:mainRet0,
  store i32 1, i32* %retVal3, align 4
  br label %mainRet0
if.end26:            ;preds: whileNext24,    succs:mainRet0,
  store i32 0, i32* %retVal3, align 4
  br label %mainRet0
mainRet0:            ;preds: if.then25,if.end26,    succs:
  %51 = load i32, i32* %retVal3, align 4
  ret i32 %51
}
