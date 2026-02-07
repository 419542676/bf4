.globl	main
fib:
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
	sw t0, -24(fp)				# 23
	j  fibRet0				# 24

if.end6:
	addi t1, t0, -1				# 12
	addi a0, t1, 0				# 13
	addi sp, sp, -32
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
	sd t3, 24(sp)
	jal ra, fib				# 14
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	ld t3, 24(sp)
	addi sp, sp, 32
	addi t1, a0, 0				# 15
	addi t2, t0, -2				# 16
	addi a0, t2, 0				# 17
	addi sp, sp, -32
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
	sd t3, 24(sp)
	jal ra, fib				# 18
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	ld t3, 24(sp)
	addi sp, sp, 32
	addi t2, a0, 0				# 19
	addw t3, t1, t2				# 20
	sw t3, -24(fp)				# 21
	j  fibRet0				# 22

fibRet0:
	lw t0, -24(fp)				# 25
	addi a0, t0, 0				# 26
	ld s1, 0(sp)
	addi sp, sp, 64				# 27
	ld ra, -8(sp)				# 28
	ld fp, -16(sp)				# 29
	jr ra					# 30

main:
	sd ra, -8(sp)				# 31
	sd fp, -16(sp)				# 32
	add fp, sp, zero				# 33
	addi sp, sp, -64				# 34
	sd s1, 0(sp)
	addi a0, zero, 35				# 35
	addi sp, sp, -16
	sd t0, 0(sp)
	jal ra, fib				# 36
	ld t0, 0(sp)
	addi sp, sp, 16
	addi t0, a0, 0				# 37
	j  mainRet7				# 38

mainRet7:
	addi a0, t0, 0				# 39
	ld s1, 0(sp)
	addi sp, sp, 64				# 40
	ld ra, -8(sp)				# 41
	ld fp, -16(sp)				# 42
	jr ra					# 43

