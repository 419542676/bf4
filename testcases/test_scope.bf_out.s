.globl	main
func:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -64				# 3
	sd s1, 0(sp)
	addi t0, a0, 0				# 4
	j  funcEntry2				# 5

funcEntry2:
	li t1, 0				# 6
	sw t1, -24(fp)				# 7
	sw t0, -20(fp)				# 8
	lw t0, -20(fp)				# 9
	la t1, b				# 10
	lw t2, 0(t1)				# 11
	addw t1, t0, t2				# 12
	sw t1, -24(fp)				# 13
	j  funcRet0				# 14

funcRet0:
	lw t1, -24(fp)				# 15
	addi a0, t1, 0				# 16
	ld s1, 0(sp)
	addi sp, sp, 64				# 17
	ld ra, -8(sp)				# 18
	ld fp, -16(sp)				# 19
	jr ra					# 20

main:
	sd ra, -8(sp)				# 21
	sd fp, -16(sp)				# 22
	add fp, sp, zero				# 23
	addi sp, sp, -64				# 24
	sd s1, 0(sp)
	j  mainEntry7				# 25

mainEntry7:
	li t0, 0				# 26
	sw t0, -28(fp)				# 27
	li t0, 0				# 28
	sw t0, -32(fp)				# 29
	li t0, 0				# 30
	sw t0, -24(fp)				# 31
	j  whileCond11				# 32

whileCond11:
	lw t0, -24(fp)				# 33
	li t1, 1000000				# 34
	slt t2, t0, t1				# 35
	andi t1, t2, 1				# 36
	xori t2, t1, 0				# 37
	sltu t1, zero, t2				# 38
	bne t1, zero, doWhileBody12				# 39
	j  whileNext14				# 40

doWhileBody12:
	li t1, 5				# 41
	sw t1, -20(fp)				# 42
	lw t1, -32(fp)				# 43
	lw t2, -20(fp)				# 44
	addi a0, t2, 0				# 45
	addi sp, sp, -32
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
	jal ra, func				# 46
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	addi sp, sp, 32
	addi t2, a0, 0				# 47
	addw t0, t1, t2				# 48
	la t2, a				# 49
	lw t1, 0(t2)				# 50
	addw t2, t0, t1				# 51
	lw t1, -20(fp)				# 52
	addw t0, t2, t1				# 53
	sw t0, -32(fp)				# 54
	lw t0, -24(fp)				# 55
	addi t2, t0, 1				# 56
	sw t2, -24(fp)				# 57
	j  doWhileCond13				# 58

doWhileCond13:
	lw t2, -24(fp)				# 59
	li t0, 1000000				# 60
	slt t1, t2, t0				# 61
	andi t0, t1, 1				# 62
	xori t1, t0, 0				# 63
	sltu t0, zero, t1				# 64
	bne t0, zero, doWhileBody12				# 65
	j  whileNext14				# 66

whileNext14:
	lw t0, -32(fp)				# 67
	li t1, 255				# 68
	remw t2, t0, t1				# 69
	sw t2, -28(fp)				# 70
	j  mainRet5				# 71

mainRet5:
	lw t2, -28(fp)				# 72
	addi a0, t2, 0				# 73
	ld s1, 0(sp)
	addi sp, sp, 64				# 74
	ld ra, -8(sp)				# 75
	ld fp, -16(sp)				# 76
	jr ra					# 77

.data
a:
	.word	100
.data
b:
	.word	200
