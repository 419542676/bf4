define i32 @cube(i32 %0) {
cubeStart6:            ;No predecessor!!    succs:cubeEntry7,
  %retVal8 = alloca i32, align 4
  %n9 = alloca i32, align 4
  br label %cubeEntry7
cubeEntry7:            ;preds: cubeStart6,    succs:cubeRet5,
  store i32 0, i32* %retVal8, align 4
  store i32 %0, i32* %n9, align 4
  %1 = load i32, i32* %n9, align 4
  %2 = load i32, i32* %n9, align 4
  %3 = call i32 @square(i32 %2)
  %4 = mul i32 %1, %3
  store i32 %4, i32* %retVal8, align 4
  br label %cubeRet5
cubeRet5:            ;preds: cubeEntry7,    succs:
  %5 = load i32, i32* %retVal8, align 4
  ret i32 %5
}
define i32 @main() {
mainStart11:            ;No predecessor!!    succs:mainEntry12,
  %retVal13 = alloca i32, align 4
  %result14 = alloca i32, align 4
  br label %mainEntry12
mainEntry12:            ;preds: mainStart11,    succs:mainRet10,
  store i32 0, i32* %retVal13, align 4
  %0 = call i32 @cube(i32 3)
  store i32 %0, i32* %result14, align 4
  %1 = load i32, i32* %result14, align 4
  store i32 %1, i32* %retVal13, align 4
  br label %mainRet10
mainRet10:            ;preds: mainEntry12,    succs:
  %2 = load i32, i32* %retVal13, align 4
  ret i32 %2
}
define i32 @square(i32 %0) {
squareStart1:            ;No predecessor!!    succs:squareEntry2,
  %retVal3 = alloca i32, align 4
  %n4 = alloca i32, align 4
  br label %squareEntry2
squareEntry2:            ;preds: squareStart1,    succs:squareRet0,
  store i32 0, i32* %retVal3, align 4
  store i32 %0, i32* %n4, align 4
  %1 = load i32, i32* %n4, align 4
  %2 = load i32, i32* %n4, align 4
  %3 = mul i32 %1, %2
  store i32 %3, i32* %retVal3, align 4
  br label %squareRet0
squareRet0:            ;preds: squareEntry2,    succs:
  %4 = load i32, i32* %retVal3, align 4
  ret i32 %4
}
