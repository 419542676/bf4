define i32 @add(i32 %0, i32 %1) {
addStart1:            ;No predecessor!!    succs:addEntry2,
  %retVal3 = alloca i32, align 4
  %a4 = alloca i32, align 4
  %b5 = alloca i32, align 4
  br label %addEntry2
addEntry2:            ;preds: addStart1,    succs:addRet0,
  store i32 0, i32* %retVal3, align 4
  store i32 %0, i32* %a4, align 4
  store i32 %1, i32* %b5, align 4
  %2 = load i32, i32* %a4, align 4
  %3 = load i32, i32* %b5, align 4
  %4 = add i32 %2, %3
  store i32 %4, i32* %retVal3, align 4
  br label %addRet0
addRet0:            ;preds: addEntry2,    succs:
  %5 = load i32, i32* %retVal3, align 4
  ret i32 %5
}
define i32 @main() {
mainStart7:            ;No predecessor!!    succs:mainEntry8,
  %retVal9 = alloca i32, align 4
  %sum10 = alloca i32, align 4
  br label %mainEntry8
mainEntry8:            ;preds: mainStart7,    succs:mainRet6,
  store i32 0, i32* %retVal9, align 4
  %0 = call i32 @add(i32 5,i32 3)
  store i32 %0, i32* %sum10, align 4
  %1 = load i32, i32* %sum10, align 4
  store i32 %1, i32* %retVal9, align 4
  br label %mainRet6
mainRet6:            ;preds: mainEntry8,    succs:
  %2 = load i32, i32* %retVal9, align 4
  ret i32 %2
}
