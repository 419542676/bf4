define i32 @fib(i32 %0) {
fibStart1:            ;No predecessor!!    succs:fibEntry2,
  %retVal3 = alloca i32, align 4
  %n4 = alloca i32, align 4
  br label %fibEntry2
fibEntry2:            ;preds: fibStart1,    succs:if.then5,if.end6,
  store i32 0, i32* %retVal3, align 4
  store i32 %0, i32* %n4, align 4
  %1 = load i32, i32* %n4, align 4
  %2 = icmp eq i32 %1, 0
  %3 = zext i1 %2 to i32
  %4 = icmp ne i32 %3, 0
  br i1 %4, label %if.then5, label %if.end6
if.then5:            ;preds: fibEntry2,    succs:fibRet0,
  store i32 0, i32* %retVal3, align 4
  br label %fibRet0
if.end6:            ;preds: fibEntry2,    succs:if.then7,if.end8,
  %5 = load i32, i32* %n4, align 4
  %6 = icmp eq i32 %5, 1
  %7 = zext i1 %6 to i32
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %if.then7, label %if.end8
if.then7:            ;preds: if.end6,    succs:fibRet0,
  store i32 1, i32* %retVal3, align 4
  br label %fibRet0
if.end8:            ;preds: if.end6,    succs:fibRet0,
  %9 = load i32, i32* %n4, align 4
  %10 = sub i32 %9, 1
  %11 = call i32 @fib(i32 %10)
  %12 = load i32, i32* %n4, align 4
  %13 = sub i32 %12, 2
  %14 = call i32 @fib(i32 %13)
  %15 = add i32 %11, %14
  store i32 %15, i32* %retVal3, align 4
  br label %fibRet0
fibRet0:            ;preds: if.then5,if.then7,if.end8,    succs:
  %16 = load i32, i32* %retVal3, align 4
  ret i32 %16
}
define i32 @main() {
mainStart10:            ;No predecessor!!    succs:mainEntry11,
  %retVal12 = alloca i32, align 4
  br label %mainEntry11
mainEntry11:            ;preds: mainStart10,    succs:mainRet9,
  store i32 0, i32* %retVal12, align 4
  %0 = call i32 @fib(i32 30)
  store i32 %0, i32* %retVal12, align 4
  br label %mainRet9
mainRet9:            ;preds: mainEntry11,    succs:
  %1 = load i32, i32* %retVal12, align 4
  ret i32 %1
}
