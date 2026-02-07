define i32 @get_hidden_val() {
get_hidden_valEntry2:            ;No predecessor!!    succs:get_hidden_valRet0,
  br label %get_hidden_valRet0
get_hidden_valRet0:            ;preds: get_hidden_valEntry2,    succs:
  ret i32 10
}
define i32 @main() {
mainEntry6:            ;No predecessor!!    succs:mainRet4,
  %5 = call i32 @get_hidden_val()
  %14 = add i32 60, %5
  br label %mainRet4
mainRet4:            ;preds: mainEntry6,    succs:
  ret i32 %14
}
