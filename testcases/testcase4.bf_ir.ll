define i32 @main() {
mainStart1:            ;No predecessor!!    succs:mainEntry2,
  %retVal3 = alloca i32, align 4
  %x4 = alloca i32, align 4
  %y5 = alloca i32, align 4
  br label %mainEntry2
mainEntry2:            ;preds: mainStart1,    succs:if.then6,if.else7,
  store i32 0, i32* %retVal3, align 4
  store i32 5, i32* %x4, align 4
  store i32 10, i32* %y5, align 4
  %0 = load i32, i32* %x4, align 4
  %1 = load i32, i32* %y5, align 4
  %2 = icmp slt i32 %1, %0
  %3 = zext i1 %2 to i32
  %4 = icmp ne i32 %3, 0
  br i1 %4, label %if.then6, label %if.else7
if.then6:            ;preds: mainEntry2,    succs:mainRet0,
  %5 = load i32, i32* %x4, align 4
  store i32 %5, i32* %retVal3, align 4
  br label %mainRet0
if.else7:            ;preds: mainEntry2,    succs:mainRet0,
  %6 = load i32, i32* %y5, align 4
  store i32 %6, i32* %retVal3, align 4
  br label %mainRet0
mainRet0:            ;preds: if.then6,if.else7,    succs:
  %7 = load i32, i32* %retVal3, align 4
  ret i32 %7
}
