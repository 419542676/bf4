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
	sw t0, -44(fp)				# 6
	li t0, 100				# 7
	sw t0, -24(fp)				# 8
	li t0, 200				# 9
	sw t0, -28(fp)				# 10
	li t0, 0				# 11
	sw t0, -20(fp)				# 12
	j  if.then7				# 13

if.then7:
	li t0, 10				# 14
	sw t0, -20(fp)				# 15
	j  if.end9				# 16

if.end9:
	lw t0, -20(fp)				# 17
	sw t0, -20(fp)				# 18
	li t0, 0				# 19
	sw t0, -36(fp)				# 20
	li t0, 0				# 21
	sw t0, -48(fp)				# 22
	j  whileCond12				# 23

whileCond12:
	lw t0, -36(fp)				# 24
	li t1, 10				# 25
	slt t2, t0, t1				# 26
	andi t1, t2, 1				# 27
	xori t2, t1, 0				# 28
	sltu t1, zero, t2				# 29
	bne t1, zero, loop_preheader_018				# 30
	j  whileNext15				# 31

loop_preheader_018:
	lw t1, -24(fp)				# 32
	lw t2, -28(fp)				# 33
	addw t0, t1, t2				# 34
	j  doWhileBody13				# 35

doWhileBody13:
	sw t0, -40(fp)				# 36
	lw t2, -48(fp)				# 37
	addw t1, t2, t0				# 38
	sw t1, -48(fp)				# 39
	lw t1, -36(fp)				# 40
	addi t2, t1, 1				# 41
	sw t2, -36(fp)				# 42
	j  doWhileCond14				# 43

doWhileCond14:
	lw t2, -36(fp)				# 44
	li t1, 10				# 45
	slt t3, t2, t1				# 46
	andi t1, t3, 1				# 47
	xori t3, t1, 0				# 48
	sltu t1, zero, t3				# 49
	bne t1, zero, doWhileBody13				# 50
	j  whileNext15				# 51

whileNext15:
	lw t0, -24(fp)				# 52
	lw t1, -28(fp)				# 53
	mulw t3, t0, t1				# 54
	sw t3, -32(fp)				# 55
	lw t3, -48(fp)				# 56
	lw t1, -20(fp)				# 57
	addw t0, t3, t1				# 58
	sw t0, -44(fp)				# 59
	j  mainRet0				# 60

mainRet0:
	lw t0, -44(fp)				# 61
	addi a0, t0, 0				# 62
	ld s1, 0(sp)
	addi sp, sp, 80				# 63
	ld ra, -8(sp)				# 64
	ld fp, -16(sp)				# 65
	jr ra					# 66

