define i32 @collatz(i32 %0) {
collatzStart1:            ;No predecessor!!    succs:collatzEntry2,
  %retVal3 = alloca i32, align 4
  %n4 = alloca i32, align 4
  %step5 = alloca i32, align 4
  br label %collatzEntry2
collatzEntry2:            ;preds: collatzStart1,    succs:whileCond6,
  store i32 0, i32* %retVal3, align 4
  store i32 %0, i32* %n4, align 4
  store i32 0, i32* %step5, align 4
  br label %whileCond6
whileCond6:            ;preds: collatzEntry2,    succs:doWhileBody7,whileNext9,
  %1 = load i32, i32* %n4, align 4
  %2 = icmp ne i32 %1, 1
  %3 = zext i1 %2 to i32
  %4 = icmp ne i32 %3, 0
  br i1 %4, label %doWhileBody7, label %whileNext9
doWhileBody7:            ;preds: whileCond6,doWhileCond8,    succs:if.then10,if.else11,
  %5 = load i32, i32* %n4, align 4
  %6 = srem i32 %5, 2
  %7 = icmp eq i32 %6, 0
  %8 = zext i1 %7 to i32
  %9 = icmp ne i32 %8, 0
  br i1 %9, label %if.then10, label %if.else11
if.then10:            ;preds: doWhileBody7,    succs:if.end12,
  %10 = load i32, i32* %n4, align 4
  %11 = sdiv i32 %10, 2
  store i32 %11, i32* %n4, align 4
  br label %if.end12
if.else11:            ;preds: doWhileBody7,    succs:if.end12,
  %12 = load i32, i32* %n4, align 4
  %13 = mul i32 3, %12
  %14 = add i32 %13, 1
  store i32 %14, i32* %n4, align 4
  br label %if.end12
if.end12:            ;preds: if.then10,if.else11,    succs:doWhileCond8,
  %15 = load i32, i32* %step5, align 4
  %16 = add i32 %15, 1
  store i32 %16, i32* %step5, align 4
  br label %doWhileCond8
doWhileCond8:            ;preds: if.end12,    succs:doWhileBody7,whileNext9,
  %17 = load i32, i32* %n4, align 4
  %18 = icmp ne i32 %17, 1
  %19 = zext i1 %18 to i32
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %doWhileBody7, label %whileNext9
whileNext9:            ;preds: whileCond6,doWhileCond8,    succs:collatzRet0,
  %21 = load i32, i32* %step5, align 4
  store i32 %21, i32* %retVal3, align 4
  br label %collatzRet0
collatzRet0:            ;preds: whileNext9,    succs:
  %22 = load i32, i32* %retVal3, align 4
  ret i32 %22
}
define i32 @main() {
mainStart14:            ;No predecessor!!    succs:mainEntry15,
  %retVal16 = alloca i32, align 4
  %i17 = alloca i32, align 4
  %total_steps18 = alloca i32, align 4
  br label %mainEntry15
mainEntry15:            ;preds: mainStart14,    succs:whileCond19,
  store i32 0, i32* %retVal16, align 4
  store i32 1, i32* %i17, align 4
  store i32 0, i32* %total_steps18, align 4
  br label %whileCond19
whileCond19:            ;preds: mainEntry15,    succs:doWhileBody20,whileNext22,
  %0 = load i32, i32* %i17, align 4
  %1 = icmp slt i32 %0, 1000
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %doWhileBody20, label %whileNext22
doWhileBody20:            ;preds: whileCond19,doWhileCond21,    succs:doWhileCond21,
  %4 = load i32, i32* %total_steps18, align 4
  %5 = load i32, i32* %i17, align 4
  %6 = call i32 @collatz(i32 %5)
  %7 = add i32 %4, %6
  store i32 %7, i32* %total_steps18, align 4
  %8 = load i32, i32* %i17, align 4
  %9 = add i32 %8, 1
  store i32 %9, i32* %i17, align 4
  br label %doWhileCond21
doWhileCond21:            ;preds: doWhileBody20,    succs:doWhileBody20,whileNext22,
  %10 = load i32, i32* %i17, align 4
  %11 = icmp slt i32 %10, 1000
  %12 = zext i1 %11 to i32
  %13 = icmp ne i32 %12, 0
  br i1 %13, label %doWhileBody20, label %whileNext22
whileNext22:            ;preds: whileCond19,doWhileCond21,    succs:mainRet13,
  %14 = load i32, i32* %total_steps18, align 4
  store i32 %14, i32* %retVal16, align 4
  br label %mainRet13
mainRet13:            ;preds: whileNext22,    succs:
  %15 = load i32, i32* %retVal16, align 4
  ret i32 %15
}
