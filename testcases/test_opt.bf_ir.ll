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
  %result11 = alloca i32, align 4
  br label %mainEntry2
mainEntry2:            ;preds: mainStart1,    succs:if.then12,if.else13,
  store i32 0, i32* %retVal3, align 4
  store i32 10, i32* %a4, align 4
  store i32 20, i32* %b5, align 4
  %0 = load i32, i32* %a4, align 4
  %1 = load i32, i32* %b5, align 4
  %2 = add i32 %0, %1
  %3 = add i32 %2, 5
  store i32 %3, i32* %c6, align 4
  %4 = load i32, i32* %c6, align 4
  %5 = add i32 %4, 0
  store i32 %5, i32* %d7, align 4
  %6 = load i32, i32* %d7, align 4
  %7 = mul i32 %6, 1
  store i32 %7, i32* %e8, align 4
  store i32 100, i32* %f9, align 4
  %8 = load i32, i32* %a4, align 4
  %9 = load i32, i32* %b5, align 4
  %10 = mul i32 %8, %9
  store i32 %10, i32* %g10, align 4
  store i32 0, i32* %result11, align 4
  br i1 1, label %if.then12, label %if.else13
if.then12:            ;preds: mainEntry2,    succs:if.end14,
  %11 = load i32, i32* %e8, align 4
  store i32 %11, i32* %result11, align 4
  br label %if.end14
if.else13:            ;preds: mainEntry2,    succs:if.end14,
  store i32 999, i32* %result11, align 4
  br label %if.end14
if.end14:            ;preds: if.then12,if.else13,    succs:mainRet0,
  %12 = load i32, i32* %result11, align 4
  store i32 %12, i32* %retVal3, align 4
  br label %mainRet0
mainRet0:            ;preds: if.end14,    succs:
  %13 = load i32, i32* %retVal3, align 4
  ret i32 %13
}
