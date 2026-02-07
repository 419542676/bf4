@g_offset = dso_local global i32 20, align 4
define i32 @factorial(i32 %0) {
factorialEntry2:            ;No predecessor!!    succs:if.then5,if.end6,
  	%phi_demote_24 = alloca i32, align 4
  %2 = icmp slt i32 %0, 2
  %3 = zext i1 %2 to i32
  %4 = icmp ne i32 %3, 0
  br i1 %4, label %if.then5, label %if.end6
if.then5:            ;preds: factorialEntry2,    succs:factorialRet0,
  	store i32 1, i32* %phi_demote_24, align 4
  br label %factorialRet0
if.end6:            ;preds: factorialEntry2,    succs:factorialRet0,
  %7 = sub i32 %0, 1
  %8 = call i32 @factorial(i32 %7)
  %9 = mul i32 %0, %8
  	store i32 %9, i32* %phi_demote_24, align 4
  br label %factorialRet0
factorialRet0:            ;preds: if.then5,if.end6,    succs:
  	%phi_19 = load i32, i32* %phi_demote_24, align 4
  ret i32 %phi_19
}
define i32 @main() {
mainEntry9:            ;No predecessor!!    succs:whileCond14,
  	%phi_demote_25 = alloca i32, align 4
  	%phi_demote_26 = alloca i32, align 4
  	%phi_demote_27 = alloca i32, align 4
  br label %whileCond14
whileCond14:            ;preds: mainEntry9,    succs:doWhileBody15,whileNext17,
  %3 = zext i1 1 to i32
  %4 = icmp ne i32 %3, 0
  	store i32 0, i32* %phi_demote_25, align 4
  	store i32 0, i32* %phi_demote_26, align 4
  	store i32 0, i32* %phi_demote_27, align 4
  br i1 %4, label %doWhileBody15, label %whileNext17
doWhileBody15:            ;preds: whileCond14,doWhileCond16,    succs:doWhileCond16,
  	%phi_20 = load i32, i32* %phi_demote_25, align 4
  	%phi_22 = load i32, i32* %phi_demote_26, align 4
  %7 = add i32 %phi_20, %phi_22
  %9 = add i32 %phi_22, 1
  br label %doWhileCond16
doWhileCond16:            ;preds: doWhileBody15,    succs:doWhileBody15,whileNext17,
  %12 = icmp slt i32 %9, 5
  %13 = zext i1 %12 to i32
  %14 = icmp ne i32 %13, 0
  	store i32 %7, i32* %phi_demote_25, align 4
  	store i32 %9, i32* %phi_demote_26, align 4
  	store i32 %7, i32* %phi_demote_27, align 4
  br i1 %14, label %doWhileBody15, label %whileNext17
whileNext17:            ;preds: whileCond14,doWhileCond16,    succs:mainRet7,
  	%phi_21 = load i32, i32* %phi_demote_27, align 4
  %15 = call i32 @factorial(i32 5)
  %18 = add i32 %phi_21, %15
  %20 = add i32 %18, 20
  br label %mainRet7
mainRet7:            ;preds: whileNext17,    succs:
  ret i32 %20
}
