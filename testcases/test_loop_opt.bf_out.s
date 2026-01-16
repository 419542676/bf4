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
	sw t0, -32(fp)				# 8
	li t0, 0				# 9
	sw t0, -48(fp)				# 10
	li t0, 100				# 11
	sw t0, -20(fp)				# 12
	li t0, 200				# 13
	sw t0, -24(fp)				# 14
	j  whileCond8				# 15

whileCond8:
	lw t0, -32(fp)				# 16
	li t1, 10				# 17
	slt t2, t0, t1				# 18
	andi t1, t2, 1				# 19
	xori t2, t1, 0				# 20
	sltu t1, zero, t2				# 21
	bne t1, zero, loop_preheader_015				# 22
	j  whileNext11				# 23

loop_preheader_015:
	lw t1, -20(fp)				# 24
	lw t2, -24(fp)				# 25
	addw t0, t1, t2				# 26
	j  doWhileBody9				# 27

doWhileBody9:
	sw t0, -36(fp)				# 28
	sw t0, -44(fp)				# 29
	lw t2, -48(fp)				# 30
	addw t1, t2, t0				# 31
	sw t1, -48(fp)				# 32
	lw t1, -32(fp)				# 33
	addi t2, t1, 1				# 34
	sw t2, -32(fp)				# 35
	j  doWhileCond10				# 36

doWhileCond10:
	lw t2, -32(fp)				# 37
	li t1, 10				# 38
	slt t3, t2, t1				# 39
	andi t1, t3, 1				# 40
	xori t3, t1, 0				# 41
	sltu t1, zero, t3				# 42
	bne t1, zero, doWhileBody9				# 43
	j  whileNext11				# 44

whileNext11:
	lw t0, -20(fp)				# 45
	lw t1, -24(fp)				# 46
	mulw t3, t0, t1				# 47
	sw t3, -28(fp)				# 48
	lw t3, -48(fp)				# 49
	sw t3, -40(fp)				# 50
	j  mainRet0				# 51

mainRet0:
	lw t3, -40(fp)				# 52
	addi a0, t3, 0				# 53
	ld s1, 0(sp)
	addi sp, sp, 80				# 54
	ld ra, -8(sp)				# 55
	ld fp, -16(sp)				# 56
	jr ra					# 57

