define i32 @main() {
mainEntry2:            ;No predecessor!!    succs:if.then10,
  br label %if.then10
if.then10:            ;preds: mainEntry2,    succs:if.end12,
  br label %if.end12
if.end12:            ;preds: if.then10,    succs:whileCond13,
  %phi_27 = phi i32 [ 100, %if.then10 ]
  br label %whileCond13
whileCond13:            ;preds: if.end12,    succs:doWhileBody14,
  br label %doWhileBody14
doWhileBody14:            ;preds: whileCond13,doWhileCond15,    succs:if.then19,if.else20,
  %phi_23 = phi i32 [ 0, %whileCond13 ], [ %phi_22, %doWhileCond15 ]
  %phi_25 = phi i32 [ 0, %whileCond13 ], [ %24, %doWhileCond15 ]
  %14 = add i32 %phi_23, 200
  %16 = icmp slt i32 %phi_25, 5
  %17 = zext i1 %16 to i32
  %18 = icmp ne i32 %17, 0
  br i1 %18, label %if.then19, label %if.else20
if.then19:            ;preds: doWhileBody14,    succs:if.end21,
  %20 = add i32 %14, 1
  br label %if.end21
if.else20:            ;preds: doWhileBody14,    succs:if.end21,
  %22 = add i32 %14, 2
  br label %if.end21
if.end21:            ;preds: if.then19,if.else20,    succs:doWhileCond15,
  %phi_22 = phi i32 [ %20, %if.then19 ], [ %22, %if.else20 ]
  %24 = add i32 %phi_25, 1
  br label %doWhileCond15
doWhileCond15:            ;preds: if.end21,    succs:doWhileBody14,whileNext16,
  %27 = icmp slt i32 %24, 10
  %28 = zext i1 %27 to i32
  %29 = icmp ne i32 %28, 0
  br i1 %29, label %doWhileBody14, label %whileNext16
whileNext16:            ;preds: doWhileCond15,    succs:mainRet0,
  %phi_24 = phi i32 [ %phi_22, %doWhileCond15 ]
  %32 = add i32 %phi_27, %phi_24
  %33 = sub i32 %32, 2100
  br label %mainRet0
mainRet0:            ;preds: whileNext16,    succs:
  ret i32 %33
}
