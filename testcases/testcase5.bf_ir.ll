define i32 @doWork() {
doWorkStart1:            ;No predecessor!!    succs:doWorkEntry2,
  %retVal3 = alloca i32, align 4
  %count4 = alloca i32, align 4
  br label %doWorkEntry2
doWorkEntry2:            ;preds: doWorkStart1,    succs:whileCond5,
  store i32 0, i32* %retVal3, align 4
  store i32 0, i32* %count4, align 4
  br label %whileCond5
whileCond5:            ;preds: doWorkEntry2,    succs:doWhileBody6,whileNext8,
  %0 = load i32, i32* %count4, align 4
  %1 = icmp slt i32 %0, 5
  %2 = zext i1 %1 to i32
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %doWhileBody6, label %whileNext8
doWhileBody6:            ;preds: whileCond5,doWhileCond7,    succs:doWhileCond7,
  %4 = load i32, i32* %count4, align 4
  %5 = add i32 %4, 1
  store i32 %5, i32* %count4, align 4
  br label %doWhileCond7
doWhileCond7:            ;preds: doWhileBody6,    succs:doWhileBody6,whileNext8,
  %6 = load i32, i32* %count4, align 4
  %7 = icmp slt i32 %6, 5
  %8 = zext i1 %7 to i32
  %9 = icmp ne i32 %8, 0
  br i1 %9, label %doWhileBody6, label %whileNext8
whileNext8:            ;preds: whileCond5,doWhileCond7,    succs:doWorkRet0,
  %10 = load i32, i32* %count4, align 4
  store i32 %10, i32* %retVal3, align 4
  br label %doWorkRet0
doWorkRet0:            ;preds: whileNext8,    succs:
  %11 = load i32, i32* %retVal3, align 4
  ret i32 %11
}
define i32 @main() {
mainStart10:            ;No predecessor!!    succs:mainEntry11,
  %retVal12 = alloca i32, align 4
  %sum13 = alloca i32, align 4
  br label %mainEntry11
mainEntry11:            ;preds: mainStart10,    succs:mainRet9,
  store i32 0, i32* %retVal12, align 4
  %0 = call i32 @doWork()
  store i32 %0, i32* %sum13, align 4
  %1 = load i32, i32* %sum13, align 4
  store i32 %1, i32* %retVal12, align 4
  br label %mainRet9
mainRet9:            ;preds: mainEntry11,    succs:
  %2 = load i32, i32* %retVal12, align 4
  ret i32 %2
}
