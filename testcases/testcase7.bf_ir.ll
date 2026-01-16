define i32 @main() {
mainStart1:            ;No predecessor!!    succs:mainEntry2,
  %retVal3 = alloca i32, align 4
  %i4 = alloca i32, align 4
  %sum5 = alloca i32, align 4
  br label %mainEntry2
mainEntry2:            ;preds: mainStart1,    succs:whileCond6,
  store i32 0, i32* %retVal3, align 4
  store i32 0, i32* %i4, align 4
  store i32 0, i32* %sum5, align 4
  br label %whileCond6
whileCond6:            ;preds: mainEntry2,    succs:doWhileBody7,whileNext9,
  %0 = load i32, i32* %i4, align 4
  %1 = icmp slt i32 %0, 10000000
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %doWhileBody7, label %whileNext9
doWhileBody7:            ;preds: whileCond6,doWhileCond8,    succs:doWhileCond8,
  %4 = load i32, i32* %sum5, align 4
  %5 = load i32, i32* %i4, align 4
  %6 = add i32 %4, %5
  store i32 %6, i32* %sum5, align 4
  %7 = load i32, i32* %i4, align 4
  %8 = add i32 %7, 1
  store i32 %8, i32* %i4, align 4
  br label %doWhileCond8
doWhileCond8:            ;preds: doWhileBody7,    succs:doWhileBody7,whileNext9,
  %9 = load i32, i32* %i4, align 4
  %10 = icmp slt i32 %9, 10000000
  %11 = zext i1 %10 to i32
  %12 = icmp ne i32 %11, 0
  br i1 %12, label %doWhileBody7, label %whileNext9
whileNext9:            ;preds: whileCond6,doWhileCond8,    succs:mainRet0,
  %13 = load i32, i32* %sum5, align 4
  store i32 %13, i32* %retVal3, align 4
  br label %mainRet0
mainRet0:            ;preds: whileNext9,    succs:
  %14 = load i32, i32* %retVal3, align 4
  ret i32 %14
}
