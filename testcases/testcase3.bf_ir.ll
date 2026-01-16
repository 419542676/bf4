define i32 @main() {
mainStart1:            ;No predecessor!!    succs:mainEntry2,
  %retVal3 = alloca i32, align 4
  %arr4 = alloca [5 x i32], align 16
  %i5 = alloca i32, align 4
  br label %mainEntry2
mainEntry2:            ;preds: mainStart1,    succs:whileCond6,
  store i32 0, i32* %retVal3, align 4
  %arr4_memset = bitcast [5 x i32]* %arr4 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %arr4_memset, i8 0, i64 20, i1 false)
  %0 = getelementptr [5 x i32], [5 x i32]* %arr4, i32 0, i32 0
  store i32 1, i32* %0, align 4
  %1 = getelementptr [5 x i32], [5 x i32]* %arr4, i32 0, i32 1
  store i32 2, i32* %1, align 4
  %2 = getelementptr [5 x i32], [5 x i32]* %arr4, i32 0, i32 2
  store i32 3, i32* %2, align 4
  %3 = getelementptr [5 x i32], [5 x i32]* %arr4, i32 0, i32 3
  store i32 4, i32* %3, align 4
  %4 = getelementptr [5 x i32], [5 x i32]* %arr4, i32 0, i32 4
  store i32 5, i32* %4, align 4
  store i32 0, i32* %i5, align 4
  br label %whileCond6
whileCond6:            ;preds: mainEntry2,    succs:doWhileBody7,whileNext9,
  %5 = load i32, i32* %i5, align 4
  %6 = icmp slt i32 %5, 3
  %7 = zext i1 %6 to i32
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %doWhileBody7, label %whileNext9
doWhileBody7:            ;preds: whileCond6,doWhileCond8,    succs:doWhileCond8,
  %9 = load i32, i32* %i5, align 4
  %10 = add i32 %9, 1
  store i32 %10, i32* %i5, align 4
  %11 = getelementptr [5 x i32], [5 x i32]* %arr4, i32 0, i32 3
  %12 = getelementptr [5 x i32], [5 x i32]* %arr4, i32 0, i32 3
  %13 = load i32, i32* %12, align 4
  %14 = add i32 %13, 1
  store i32 %14, i32* %11, align 4
  br label %doWhileCond8
doWhileCond8:            ;preds: doWhileBody7,    succs:doWhileBody7,whileNext9,
  %15 = load i32, i32* %i5, align 4
  %16 = icmp slt i32 %15, 3
  %17 = zext i1 %16 to i32
  %18 = icmp ne i32 %17, 0
  br i1 %18, label %doWhileBody7, label %whileNext9
whileNext9:            ;preds: whileCond6,doWhileCond8,    succs:mainRet0,
  %19 = getelementptr [5 x i32], [5 x i32]* %arr4, i32 0, i32 3
  %20 = load i32, i32* %19, align 4
  store i32 %20, i32* %retVal3, align 4
  br label %mainRet0
mainRet0:            ;preds: whileNext9,    succs:
  %21 = load i32, i32* %retVal3, align 4
  ret i32 %21
}
