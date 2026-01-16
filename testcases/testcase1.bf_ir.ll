@a = dso_local global i32 10, align 4
@b = dso_local global i32 20, align 4
@c = dso_local global float 0x40091eb860000000, align 4
@d = dso_local global float 0x4005be76c0000000, align 4
define i32 @main() {
mainStart1:            ;No predecessor!!    succs:mainEntry2,
  %retVal3 = alloca i32, align 4
  %x4 = alloca i32, align 4
  %y5 = alloca float, align 4
  br label %mainEntry2
mainEntry2:            ;preds: mainStart1,    succs:mainRet0,
  store i32 0, i32* %retVal3, align 4
  store i32 10, i32* %x4, align 4
  store float 0x40091eb860000000, float* %y5, align 4
  %0 = load i32, i32* %x4, align 4
  store i32 %0, i32* %retVal3, align 4
  br label %mainRet0
mainRet0:            ;preds: mainEntry2,    succs:
  %1 = load i32, i32* %retVal3, align 4
  ret i32 %1
}
