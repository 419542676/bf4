define i32 @main() {
mainEntry2:            ;No predecessor!!    succs:if.then10,if.else11,
  	%phi_demote_32 = alloca i32, align 4
  	%phi_demote_33 = alloca i32, align 4
  	%phi_demote_34 = alloca i32, align 4
  	%phi_demote_35 = alloca i32, align 4
  	%phi_demote_36 = alloca i32, align 4
  br i1 1, label %if.then10, label %if.else11
if.then10:            ;preds: mainEntry2,    succs:if.end12,
  	store i32 100, i32* %phi_demote_32, align 4
  br label %if.end12
if.else11:            ;preds: mainEntry2,    succs:if.end12,
  	store i32 999, i32* %phi_demote_32, align 4
  br label %if.end12
if.end12:            ;preds: if.then10,if.else11,    succs:whileCond13,
  	%phi_27 = load i32, i32* %phi_demote_32, align 4
  br label %whileCond13
whileCond13:            ;preds: if.end12,    succs:doWhileBody14,whileNext16,
  %5 = zext i1 1 to i32
  %6 = icmp ne i32 %5, 0
  	store i32 0, i32* %phi_demote_33, align 4
  	store i32 0, i32* %phi_demote_34, align 4
  	store i32 0, i32* %phi_demote_36, align 4
  br i1 %6, label %doWhileBody14, label %whileNext16
doWhileBody14:            ;preds: whileCond13,doWhileCond15,    succs:if.then19,if.else20,
  	%phi_23 = load i32, i32* %phi_demote_33, align 4
  	%phi_25 = load i32, i32* %phi_demote_34, align 4
  %14 = add i32 %phi_23, 200
  %16 = icmp slt i32 %phi_25, 5
  %17 = zext i1 %16 to i32
  %18 = icmp ne i32 %17, 0
  br i1 %18, label %if.then19, label %if.else20
if.then19:            ;preds: doWhileBody14,    succs:if.end21,
  %20 = add i32 %14, 1
  	store i32 %20, i32* %phi_demote_35, align 4
  br label %if.end21
if.else20:            ;preds: doWhileBody14,    succs:if.end21,
  %22 = add i32 %14, 2
  	store i32 %22, i32* %phi_demote_35, align 4
  br label %if.end21
if.end21:            ;preds: if.then19,if.else20,    succs:doWhileCond15,
  	%phi_22 = load i32, i32* %phi_demote_35, align 4
  %24 = add i32 %phi_25, 1
  br label %doWhileCond15
doWhileCond15:            ;preds: if.end21,    succs:doWhileBody14,whileNext16,
  %27 = icmp slt i32 %24, 10
  %28 = zext i1 %27 to i32
  %29 = icmp ne i32 %28, 0
  	store i32 %phi_22, i32* %phi_demote_33, align 4
  	store i32 %24, i32* %phi_demote_34, align 4
  	store i32 %phi_22, i32* %phi_demote_36, align 4
  br i1 %29, label %doWhileBody14, label %whileNext16
whileNext16:            ;preds: whileCond13,doWhileCond15,    succs:mainRet0,
  	%phi_24 = load i32, i32* %phi_demote_36, align 4
  %32 = add i32 %phi_27, %phi_24
  %33 = sub i32 %32, 2100
  br label %mainRet0
mainRet0:            ;preds: whileNext16,    succs:
  ret i32 %33
}
