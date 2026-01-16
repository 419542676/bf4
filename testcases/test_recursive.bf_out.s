.globl	main
fib:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -64				# 3
	sd s1, 0(sp)
	addi t0, a0, 0				# 4
	j  fibEntry2				# 5

fibEntry2:
	li t1, 0				# 6
	sw t1, -24(fp)				# 7
	sw t0, -20(fp)				# 8
	lw t0, -20(fp)				# 9
	xori t1, t0, 0				# 10
	sltu t0, zero, t1				# 11
	xori t0, t0, 1				# 12
	andi t1, t0, 1				# 13
	xori t0, t1, 0				# 14
	sltu t1, zero, t0				# 15
	bne t1, zero, if.then5				# 16
	j  if.end6				# 17

if.then5:
	li t0, 0				# 43
	sw t0, -24(fp)				# 44
	j  fibRet0				# 45

if.end6:
	lw t1, -20(fp)				# 18
	xori t0, t1, 1				# 19
	sltu t1, zero, t0				# 20
	xori t1, t1, 1				# 21
	andi t0, t1, 1				# 22
	xori t1, t0, 0				# 23
	sltu t0, zero, t1				# 24
	bne t0, zero, if.then7				# 25
	j  if.end8				# 26

if.then7:
	li t0, 1				# 40
	sw t0, -24(fp)				# 41
	j  fibRet0				# 42

if.end8:
	lw t0, -20(fp)				# 27
	addi t1, t0, -1				# 28
	addi a0, t1, 0				# 29
	addi sp, sp, -32
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
	jal ra, fib				# 30
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	addi sp, sp, 32
	addi t1, a0, 0				# 31
	lw t0, -20(fp)				# 32
	addi t2, t0, -2				# 33
	addi a0, t2, 0				# 34
	addi sp, sp, -32
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
	jal ra, fib				# 35
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	addi sp, sp, 32
	addi t2, a0, 0				# 36
	addw t0, t1, t2				# 37
	sw t0, -24(fp)				# 38
	j  fibRet0				# 39

fibRet0:
	lw t0, -24(fp)				# 46
	addi a0, t0, 0				# 47
	ld s1, 0(sp)
	addi sp, sp, 64				# 48
	ld ra, -8(sp)				# 49
	ld fp, -16(sp)				# 50
	jr ra					# 51

main:
	sd ra, -8(sp)				# 52
	sd fp, -16(sp)				# 53
	add fp, sp, zero				# 54
	addi sp, sp, -64				# 55
	sd s1, 0(sp)
	j  mainEntry11				# 56

mainEntry11:
	li t0, 0				# 57
	sw t0, -20(fp)				# 58
	addi a0, zero, 30				# 59
	addi sp, sp, -16
	sd t0, 0(sp)
	jal ra, fib				# 60
	ld t0, 0(sp)
	addi sp, sp, 16
	addi t0, a0, 0				# 61
	sw t0, -20(fp)				# 62
	j  mainRet9				# 63

mainRet9:
	lw t0, -20(fp)				# 64
	addi a0, t0, 0				# 65
	ld s1, 0(sp)
	addi sp, sp, 64				# 66
	ld ra, -8(sp)				# 67
	ld fp, -16(sp)				# 68
	jr ra					# 69

