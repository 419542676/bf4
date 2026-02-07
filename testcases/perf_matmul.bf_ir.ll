@A = dso_local global [400 x i32] zeroinitializer, align 16
@B = dso_local global [400 x i32] zeroinitializer, align 16
@C = dso_local global [400 x i32] zeroinitializer, align 16
define i32 @main() {
mainEntry2:            ;No predecessor!!    succs:whileCond8,
  	%phi_demote_66 = alloca i32, align 4
  	%phi_demote_67 = alloca i32, align 4
  	%phi_demote_68 = alloca i32, align 4
  	%phi_demote_69 = alloca i32, align 4
  	%phi_demote_70 = alloca i32, align 4
  	%phi_demote_71 = alloca i32, align 4
  	%phi_demote_72 = alloca i32, align 4
  	%phi_demote_73 = alloca i32, align 4
  	%phi_demote_74 = alloca i32, align 4
  	%phi_demote_75 = alloca i32, align 4
  	%phi_demote_76 = alloca i32, align 4
  	%phi_demote_77 = alloca i32, align 4
  	%phi_demote_78 = alloca i32, align 4
  	%phi_demote_79 = alloca i32, align 4
  	%phi_demote_80 = alloca i32, align 4
  	%phi_demote_81 = alloca i32, align 4
  	%phi_demote_82 = alloca i32, align 4
  	%phi_demote_83 = alloca i32, align 4
  	%phi_demote_84 = alloca i32, align 4
  	%phi_demote_85 = alloca i32, align 4
  	%phi_demote_86 = alloca i32, align 4
  	%phi_demote_87 = alloca i32, align 4
  br label %whileCond8
whileCond8:            ;preds: mainEntry2,    succs:doWhileBody9,whileNext11,
  %5 = zext i1 1 to i32
  %6 = icmp ne i32 %5, 0
  	store i32 0, i32* %phi_demote_66, align 4
  br i1 %6, label %doWhileBody9, label %whileNext11
doWhileBody9:            ;preds: whileCond8,doWhileCond10,    succs:doWhileCond10,
  	%phi_34 = load i32, i32* %phi_demote_66, align 4
  %8 = getelementptr [400 x i32], [400 x i32]* @A, i32 0, i32 %phi_34
  %10 = srem i32 %phi_34, 10
  	store i32 %10, i32* %8, align 4
  %12 = getelementptr [400 x i32], [400 x i32]* @B, i32 0, i32 %phi_34
  %14 = srem i32 %phi_34, 5
  	store i32 %14, i32* %12, align 4
  %16 = add i32 %phi_34, 1
  br label %doWhileCond10
doWhileCond10:            ;preds: doWhileBody9,    succs:doWhileBody9,whileNext11,
  %21 = icmp slt i32 %16, 400
  %22 = zext i1 %21 to i32
  %23 = icmp ne i32 %22, 0
  	store i32 %16, i32* %phi_demote_66, align 4
  br i1 %23, label %doWhileBody9, label %whileNext11
whileNext11:            ;preds: whileCond8,doWhileCond10,    succs:whileCond12,
  br label %whileCond12
whileCond12:            ;preds: whileNext11,    succs:doWhileBody13,whileNext15,
  %27 = zext i1 1 to i32
  %28 = icmp ne i32 %27, 0
  	store i32 undef, i32* %phi_demote_67, align 4
  	store i32 0, i32* %phi_demote_68, align 4
  	store i32 0, i32* %phi_demote_69, align 4
  	store i32 undef, i32* %phi_demote_70, align 4
  	store i32 undef, i32* %phi_demote_71, align 4
  	store i32 undef, i32* %phi_demote_72, align 4
  br i1 %28, label %doWhileBody13, label %whileNext15
doWhileBody13:            ;preds: whileCond12,doWhileCond14,    succs:whileCond16,
  	%phi_30 = load i32, i32* %phi_demote_67, align 4
  	%phi_32 = load i32, i32* %phi_demote_68, align 4
  	%phi_44 = load i32, i32* %phi_demote_69, align 4
  	%phi_50 = load i32, i32* %phi_demote_70, align 4
  	%phi_56 = load i32, i32* %phi_demote_71, align 4
  	%phi_62 = load i32, i32* %phi_demote_72, align 4
  br label %whileCond16
whileCond16:            ;preds: doWhileBody13,    succs:loop_preheader_165,whileNext19,
  %32 = zext i1 1 to i32
  %33 = icmp ne i32 %32, 0
  	store i32 0, i32* %phi_demote_73, align 4
  	store i32 %phi_56, i32* %phi_demote_74, align 4
  	store i32 %phi_62, i32* %phi_demote_75, align 4
  	store i32 %phi_30, i32* %phi_demote_82, align 4
  	store i32 0, i32* %phi_demote_83, align 4
  	store i32 %phi_44, i32* %phi_demote_84, align 4
  	store i32 %phi_50, i32* %phi_demote_85, align 4
  	store i32 %phi_56, i32* %phi_demote_86, align 4
  	store i32 %phi_62, i32* %phi_demote_87, align 4
  br i1 %33, label %loop_preheader_165, label %whileNext19
loop_preheader_165:            ;preds: whileCond16,    succs:doWhileBody17,
  %67 = mul i32 %phi_32, 20
  br label %doWhileBody17
doWhileBody17:            ;preds: doWhileCond18,loop_preheader_165,    succs:whileCond21,
  	%phi_36 = load i32, i32* %phi_demote_73, align 4
  	%phi_54 = load i32, i32* %phi_demote_74, align 4
  	%phi_60 = load i32, i32* %phi_demote_75, align 4
  br label %whileCond21
whileCond21:            ;preds: doWhileBody17,    succs:loop_preheader_064,whileNext24,
  %37 = zext i1 1 to i32
  %38 = icmp ne i32 %37, 0
  	store i32 0, i32* %phi_demote_76, align 4
  	store i32 0, i32* %phi_demote_77, align 4
  	store i32 0, i32* %phi_demote_78, align 4
  	store i32 0, i32* %phi_demote_79, align 4
  	store i32 %phi_54, i32* %phi_demote_80, align 4
  	store i32 %phi_60, i32* %phi_demote_81, align 4
  br i1 %38, label %loop_preheader_064, label %whileNext24
loop_preheader_064:            ;preds: whileCond21,    succs:doWhileBody22,
  %41 = mul i32 %phi_32, 20
  br label %doWhileBody22
doWhileBody22:            ;preds: doWhileCond23,loop_preheader_064,    succs:doWhileCond23,
  	%phi_40 = load i32, i32* %phi_demote_76, align 4
  	%phi_46 = load i32, i32* %phi_demote_77, align 4
  %43 = add i32 %41, %phi_40
  %46 = mul i32 %phi_40, 20
  %48 = add i32 %46, %phi_36
  %51 = getelementptr [400 x i32], [400 x i32]* @A, i32 0, i32 %43
  	%52 = load i32, i32* %51, align 4
  %54 = getelementptr [400 x i32], [400 x i32]* @B, i32 0, i32 %48
  	%55 = load i32, i32* %54, align 4
  %56 = mul i32 %52, %55
  %57 = add i32 %phi_46, %56
  %59 = add i32 %phi_40, 1
  br label %doWhileCond23
doWhileCond23:            ;preds: doWhileBody22,    succs:doWhileBody22,whileNext24,
  %62 = icmp slt i32 %59, 20
  %63 = zext i1 %62 to i32
  %64 = icmp ne i32 %63, 0
  	store i32 %59, i32* %phi_demote_76, align 4
  	store i32 %57, i32* %phi_demote_77, align 4
  	store i32 %59, i32* %phi_demote_78, align 4
  	store i32 %57, i32* %phi_demote_79, align 4
  	store i32 %43, i32* %phi_demote_80, align 4
  	store i32 %48, i32* %phi_demote_81, align 4
  br i1 %64, label %doWhileBody22, label %whileNext24
whileNext24:            ;preds: whileCond21,doWhileCond23,    succs:doWhileCond18,
  	%phi_41 = load i32, i32* %phi_demote_78, align 4
  	%phi_47 = load i32, i32* %phi_demote_79, align 4
  	%phi_53 = load i32, i32* %phi_demote_80, align 4
  	%phi_59 = load i32, i32* %phi_demote_81, align 4
  %69 = add i32 %67, %phi_36
  %71 = getelementptr [400 x i32], [400 x i32]* @C, i32 0, i32 %69
  	store i32 %phi_47, i32* %71, align 4
  %74 = add i32 %phi_36, 1
  br label %doWhileCond18
doWhileCond18:            ;preds: whileNext24,    succs:doWhileBody17,whileNext19,
  %77 = icmp slt i32 %74, 20
  %78 = zext i1 %77 to i32
  %79 = icmp ne i32 %78, 0
  	store i32 %74, i32* %phi_demote_73, align 4
  	store i32 %phi_53, i32* %phi_demote_74, align 4
  	store i32 %phi_59, i32* %phi_demote_75, align 4
  	store i32 %69, i32* %phi_demote_82, align 4
  	store i32 %74, i32* %phi_demote_83, align 4
  	store i32 %phi_41, i32* %phi_demote_84, align 4
  	store i32 %phi_47, i32* %phi_demote_85, align 4
  	store i32 %phi_53, i32* %phi_demote_86, align 4
  	store i32 %phi_59, i32* %phi_demote_87, align 4
  br i1 %79, label %doWhileBody17, label %whileNext19
whileNext19:            ;preds: whileCond16,doWhileCond18,    succs:doWhileCond14,
  	%phi_29 = load i32, i32* %phi_demote_82, align 4
  	%phi_37 = load i32, i32* %phi_demote_83, align 4
  	%phi_43 = load i32, i32* %phi_demote_84, align 4
  	%phi_49 = load i32, i32* %phi_demote_85, align 4
  	%phi_55 = load i32, i32* %phi_demote_86, align 4
  	%phi_61 = load i32, i32* %phi_demote_87, align 4
  %81 = add i32 %phi_32, 1
  br label %doWhileCond14
doWhileCond14:            ;preds: whileNext19,    succs:doWhileBody13,whileNext15,
  %84 = icmp slt i32 %81, 20
  %85 = zext i1 %84 to i32
  %86 = icmp ne i32 %85, 0
  	store i32 %phi_29, i32* %phi_demote_67, align 4
  	store i32 %81, i32* %phi_demote_68, align 4
  	store i32 %phi_43, i32* %phi_demote_69, align 4
  	store i32 %phi_49, i32* %phi_demote_70, align 4
  	store i32 %phi_55, i32* %phi_demote_71, align 4
  	store i32 %phi_61, i32* %phi_demote_72, align 4
  br i1 %86, label %doWhileBody13, label %whileNext15
whileNext15:            ;preds: whileCond12,doWhileCond14,    succs:mainRet0,
  %87 = getelementptr [400 x i32], [400 x i32]* @C, i32 0, i32 210
  	%88 = load i32, i32* %87, align 4
  br label %mainRet0
mainRet0:            ;preds: whileNext15,    succs:
  ret i32 %88
}
