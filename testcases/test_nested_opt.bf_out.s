.globl	main
main:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -80				# 3
	sd s1, 0(sp)
	j  mainEntry2				# 4

mainEntry2:
	li t0, 0				# 5
	sw t0, -40(fp)				# 6
	li t0, 0				# 7
	sw t0, -44(fp)				# 8
	li t0, 0				# 9
	sw t0, -28(fp)				# 10
	li t0, 10				# 11
	sw t0, -24(fp)				# 12
	li t0, 20				# 13
	sw t0, -20(fp)				# 14
	j  whileCond8				# 15

whileCond8:
	lw t0, -28(fp)				# 16
	li t1, 5				# 17
	slt t2, t0, t1				# 18
	andi t1, t2, 1				# 19
	xori t2, t1, 0				# 20
	sltu t1, zero, t2				# 21
	bne t1, zero, doWhileBody9				# 22
	j  whileNext11				# 23

doWhileBody9:
	li t1, 0				# 24
	sw t1, -36(fp)				# 25
	j  whileCond13				# 26

whileCond13:
	lw t1, -36(fp)				# 27
	li t2, 5				# 28
	slt t0, t1, t2				# 29
	andi t2, t0, 1				# 30
	xori t0, t2, 0				# 31
	sltu t2, zero, t0				# 32
	bne t2, zero, loop_preheader_020				# 33
	j  whileNext16				# 34

loop_preheader_020:
	lw t2, -24(fp)				# 35
	lw t0, -20(fp)				# 36
	addw t1, t2, t0				# 37
	j  doWhileBody14				# 38

doWhileBody14:
	sw t1, -32(fp)				# 39
	lw t0, -44(fp)				# 40
	addw t2, t0, t1				# 41
	sw t2, -44(fp)				# 42
	lw t2, -36(fp)				# 43
	addi t0, t2, 1				# 44
	sw t0, -36(fp)				# 45
	j  doWhileCond15				# 46

doWhileCond15:
	lw t0, -36(fp)				# 47
	li t2, 5				# 48
	slt t3, t0, t2				# 49
	andi t2, t3, 1				# 50
	xori t3, t2, 0				# 51
	sltu t2, zero, t3				# 52
	bne t2, zero, doWhileBody14				# 53
	j  whileNext16				# 54

whileNext16:
	lw t1, -28(fp)				# 55
	addi t2, t1, 1				# 56
	sw t2, -28(fp)				# 57
	j  doWhileCond10				# 58

doWhileCond10:
	lw t2, -28(fp)				# 59
	li t1, 5				# 60
	slt t3, t2, t1				# 61
	andi t1, t3, 1				# 62
	xori t3, t1, 0				# 63
	sltu t1, zero, t3				# 64
	bne t1, zero, doWhileBody9				# 65
	j  whileNext11				# 66

whileNext11:
	j  if.end19				# 67

if.end19:
	lw t1, -44(fp)				# 68
	sw t1, -40(fp)				# 69
	j  mainRet0				# 70

mainRet0:
	lw t1, -40(fp)				# 71
	addi a0, t1, 0				# 72
	ld s1, 0(sp)
	addi sp, sp, 80				# 73
	ld ra, -8(sp)				# 74
	ld fp, -16(sp)				# 75
	jr ra					# 76

