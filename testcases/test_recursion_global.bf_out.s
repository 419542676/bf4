.globl	main
factorial:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -64				# 3
	sd s1, 0(sp)
	addi t0, a0, 0				# 4
	li t1, 2				# 5
	slt t2, t0, t1				# 6
	andi t1, t2, 1				# 7
	xori t2, t1, 0				# 8
	sltu t1, zero, t2				# 9
	bne t1, zero, if.then5				# 10
	j  if.end6				# 11

if.then5:
	li t2, 1				# 19
	sw t2, -24(fp)				# 20
	j  factorialRet0				# 21

if.end6:
	addi t1, t0, -1				# 12
	addi a0, t1, 0				# 13
	addi sp, sp, -32
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
	jal ra, factorial				# 14
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	addi sp, sp, 32
	addi t1, a0, 0				# 15
	mulw t2, t0, t1				# 16
	sw t2, -24(fp)				# 17
	j  factorialRet0				# 18

factorialRet0:
	lw t2, -24(fp)				# 22
	addi a0, t2, 0				# 23
	ld s1, 0(sp)
	addi sp, sp, 64				# 24
	ld ra, -8(sp)				# 25
	ld fp, -16(sp)				# 26
	jr ra					# 27

main:
	sd ra, -8(sp)				# 28
	sd fp, -16(sp)				# 29
	add fp, sp, zero				# 30
	addi sp, sp, -80				# 31
	sd s1, 0(sp)
	j  whileCond14				# 32

whileCond14:
	andi t1, t0, 1				# 33
	xori t0, t1, 0				# 34
	sltu t1, zero, t0				# 35
	li t0, 0				# 36
	sw t0, -32(fp)				# 37
	li t0, 0				# 38
	sw t0, -36(fp)				# 39
	li t0, 0				# 40
	sw t0, -40(fp)				# 41
	bne t1, zero, doWhileBody15				# 42
	j  whileNext17				# 43

doWhileBody15:
	lw t1, -32(fp)				# 44
	lw t0, -36(fp)				# 45
	addw t2, t1, t0				# 46
	addi t1, t0, 1				# 47
	j  doWhileCond16				# 48

doWhileCond16:
	li t0, 5				# 49
	slt t3, t1, t0				# 50
	andi t0, t3, 1				# 51
	xori t3, t0, 0				# 52
	sltu t0, zero, t3				# 53
	sw t2, -32(fp)				# 54
	sw t1, -36(fp)				# 55
	sw t2, -40(fp)				# 56
	bne t0, zero, doWhileBody15				# 57
	j  whileNext17				# 58

whileNext17:
	lw t0, -40(fp)				# 59
	addi a0, zero, 5				# 60
	addi sp, sp, -32
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
	sd t3, 24(sp)
	jal ra, factorial				# 61
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	ld t3, 24(sp)
	addi sp, sp, 32
	addi t2, a0, 0				# 62
	addw t1, t0, t2				# 63
	addi t0, t1, 20				# 64
	j  mainRet7				# 65

mainRet7:
	addi a0, t0, 0				# 66
	ld s1, 0(sp)
	addi sp, sp, 80				# 67
	ld ra, -8(sp)				# 68
	ld fp, -16(sp)				# 69
	jr ra					# 70

.data
g_offset:
	.word	20
