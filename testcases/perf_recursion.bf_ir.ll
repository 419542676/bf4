define i32 @fib(i32 %0) {
fibEntry2:            ;No predecessor!!    succs:if.then5,if.end6,
  	%phi_demote_13 = alloca i32, align 4
  %2 = icmp slt i32 %0, 2
  %3 = zext i1 %2 to i32
  %4 = icmp ne i32 %3, 0
  br i1 %4, label %if.then5, label %if.end6
if.then5:            ;preds: fibEntry2,    succs:fibRet0,
  	store i32 %0, i32* %phi_demote_13, align 4
  br label %fibRet0
if.end6:            ;preds: fibEntry2,    succs:fibRet0,
  %7 = sub i32 %0, 1
  %8 = call i32 @fib(i32 %7)
  %10 = sub i32 %0, 2
  %11 = call i32 @fib(i32 %10)
  %12 = add i32 %8, %11
  	store i32 %12, i32* %phi_demote_13, align 4
  br label %fibRet0
fibRet0:            ;preds: if.then5,if.end6,    succs:
  	%phi_12 = load i32, i32* %phi_demote_13, align 4
  ret i32 %phi_12
}
define i32 @main() {
mainEntry9:            ;No predecessor!!    succs:mainRet7,
  %1 = call i32 @fib(i32 35)
  br label %mainRet7
mainRet7:            ;preds: mainEntry9,    succs:
  ret i32 %1
}
