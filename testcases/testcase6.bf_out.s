.globl	main
cube:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -64				# 3
	sd s1, 0(sp)
	addi t0, a0, 0				# 4
	j  cubeEntry7				# 5

cubeEntry7:
	li t1, 0				# 6
	sw t1, -24(fp)				# 7
	sw t0, -20(fp)				# 8
	lw t0, -20(fp)				# 9
	lw t1, -20(fp)				# 10
	addi a0, t1, 0				# 11
	addi sp, sp, -32
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
	jal ra, square				# 12
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	addi sp, sp, 32
	addi t1, a0, 0				# 13
	mulw t2, t0, t1				# 14
	sw t2, -24(fp)				# 15
	j  cubeRet5				# 16

cubeRet5:
	lw t2, -24(fp)				# 17
	addi a0, t2, 0				# 18
	ld s1, 0(sp)
	addi sp, sp, 64				# 19
	ld ra, -8(sp)				# 20
	ld fp, -16(sp)				# 21
	jr ra					# 22

main:
	sd ra, -8(sp)				# 23
	sd fp, -16(sp)				# 24
	add fp, sp, zero				# 25
	addi sp, sp, -64				# 26
	sd s1, 0(sp)
	j  mainEntry12				# 27

mainEntry12:
	li t0, 0				# 28
	sw t0, -24(fp)				# 29
	addi a0, zero, 3				# 30
	addi sp, sp, -16
	sd t0, 0(sp)
	jal ra, cube				# 31
	ld t0, 0(sp)
	addi sp, sp, 16
	addi t0, a0, 0				# 32
	sw t0, -20(fp)				# 33
	lw t0, -20(fp)				# 34
	sw t0, -24(fp)				# 35
	j  mainRet10				# 36

mainRet10:
	lw t0, -24(fp)				# 37
	addi a0, t0, 0				# 38
	ld s1, 0(sp)
	addi sp, sp, 64				# 39
	ld ra, -8(sp)				# 40
	ld fp, -16(sp)				# 41
	jr ra					# 42

square:
	sd ra, -8(sp)				# 43
	sd fp, -16(sp)				# 44
	add fp, sp, zero				# 45
	addi sp, sp, -64				# 46
	sd s1, 0(sp)
	addi t0, a0, 0				# 47
	j  squareEntry2				# 48

squareEntry2:
	li t1, 0				# 49
	sw t1, -24(fp)				# 50
	sw t0, -20(fp)				# 51
	lw t0, -20(fp)				# 52
	lw t1, -20(fp)				# 53
	mulw t2, t0, t1				# 54
	sw t2, -24(fp)				# 55
	j  squareRet0				# 56

squareRet0:
	lw t2, -24(fp)				# 57
	addi a0, t2, 0				# 58
	ld s1, 0(sp)
	addi sp, sp, 64				# 59
	ld ra, -8(sp)				# 60
	ld fp, -16(sp)				# 61
	jr ra					# 62

