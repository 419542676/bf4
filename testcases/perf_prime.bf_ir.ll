define i32 @is_prime(i32 %0) {
is_primeEntry2:            ;No predecessor!!    succs:if.then5,if.end6,
  	%phi_demote_35 = alloca i32, align 4
  	%phi_demote_36 = alloca i32, align 4
  	%phi_demote_37 = alloca i32, align 4
  %2 = icmp slt i32 %0, 2
  %3 = zext i1 %2 to i32
  %4 = icmp ne i32 %3, 0
  br i1 %4, label %if.then5, label %if.end6
if.then5:            ;preds: is_primeEntry2,    succs:is_primeRet0,
  	store i32 0, i32* %phi_demote_37, align 4
  br label %is_primeRet0
if.end6:            ;preds: is_primeEntry2,    succs:whileCond8,
  br label %whileCond8
whileCond8:            ;preds: if.end6,    succs:doWhileBody9,whileNext11,
  %9 = icmp sle i32 4, %0
  %10 = zext i1 %9 to i32
  %11 = icmp ne i32 %10, 0
  	store i32 2, i32* %phi_demote_35, align 4
  	store i32 2, i32* %phi_demote_36, align 4
  br i1 %11, label %doWhileBody9, label %whileNext11
doWhileBody9:            ;preds: whileCond8,doWhileCond10,    succs:if.then12,if.end13,
  	%phi_27 = load i32, i32* %phi_demote_35, align 4
  %14 = srem i32 %0, %phi_27
  %15 = icmp eq i32 %14, 0
  %16 = zext i1 %15 to i32
  %17 = icmp ne i32 %16, 0
  br i1 %17, label %if.then12, label %if.end13
if.then12:            ;preds: doWhileBody9,    succs:is_primeRet0,
  	store i32 0, i32* %phi_demote_37, align 4
  br label %is_primeRet0
if.end13:            ;preds: doWhileBody9,    succs:doWhileCond10,
  %19 = add i32 %phi_27, 1
  br label %doWhileCond10
doWhileCond10:            ;preds: if.end13,    succs:doWhileBody9,whileNext11,
  %22 = mul i32 %19, %19
  %24 = icmp sle i32 %22, %0
  %25 = zext i1 %24 to i32
  %26 = icmp ne i32 %25, 0
  	store i32 %19, i32* %phi_demote_35, align 4
  	store i32 %19, i32* %phi_demote_36, align 4
  br i1 %26, label %doWhileBody9, label %whileNext11
whileNext11:            ;preds: whileCond8,doWhileCond10,    succs:is_primeRet0,
  	%phi_28 = load i32, i32* %phi_demote_36, align 4
  	store i32 1, i32* %phi_demote_37, align 4
  br label %is_primeRet0
is_primeRet0:            ;preds: if.then5,if.then12,whileNext11,    succs:
  	%phi_26 = load i32, i32* %phi_demote_37, align 4
  ret i32 %phi_26
}
define i32 @main() {
mainEntry16:            ;No predecessor!!    succs:whileCond20,
  	%phi_demote_38 = alloca i32, align 4
  	%phi_demote_39 = alloca i32, align 4
  	%phi_demote_40 = alloca i32, align 4
  	%phi_demote_41 = alloca i32, align 4
  br label %whileCond20
whileCond20:            ;preds: mainEntry16,    succs:doWhileBody21,whileNext23,
  %2 = zext i1 1 to i32
  %3 = icmp ne i32 %2, 0
  	store i32 0, i32* %phi_demote_38, align 4
  	store i32 0, i32* %phi_demote_39, align 4
  	store i32 0, i32* %phi_demote_41, align 4
  br i1 %3, label %doWhileBody21, label %whileNext23
doWhileBody21:            ;preds: whileCond20,doWhileCond22,    succs:if.then24,if.end25,
  	%phi_31 = load i32, i32* %phi_demote_38, align 4
  	%phi_33 = load i32, i32* %phi_demote_39, align 4
  %5 = call i32 @is_prime(i32 %phi_33)
  %6 = icmp ne i32 %5, 0
  	store i32 %phi_31, i32* %phi_demote_40, align 4
  br i1 %6, label %if.then24, label %if.end25
if.then24:            ;preds: doWhileBody21,    succs:if.end25,
  %8 = add i32 %phi_31, 1
  	store i32 %8, i32* %phi_demote_40, align 4
  br label %if.end25
if.end25:            ;preds: doWhileBody21,if.then24,    succs:doWhileCond22,
  	%phi_30 = load i32, i32* %phi_demote_40, align 4
  %10 = add i32 %phi_33, 1
  br label %doWhileCond22
doWhileCond22:            ;preds: if.end25,    succs:doWhileBody21,whileNext23,
  %12 = icmp slt i32 %10, 50000
  %13 = zext i1 %12 to i32
  %14 = icmp ne i32 %13, 0
  	store i32 %phi_30, i32* %phi_demote_38, align 4
  	store i32 %10, i32* %phi_demote_39, align 4
  	store i32 %phi_30, i32* %phi_demote_41, align 4
  br i1 %14, label %doWhileBody21, label %whileNext23
whileNext23:            ;preds: whileCond20,doWhileCond22,    succs:mainRet14,
  	%phi_32 = load i32, i32* %phi_demote_41, align 4
  br label %mainRet14
mainRet14:            ;preds: whileNext23,    succs:
  ret i32 %phi_32
}
