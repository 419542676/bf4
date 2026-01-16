.globl	main
main:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -96				# 3
	sd s1, 0(sp)
	j  mainEntry2				# 4

mainEntry2:
	li t0, 0				# 5
	sw t0, -52(fp)				# 6
	li t0, 10				# 7
	sw t0, -20(fp)				# 8
	li t0, 20				# 9
	sw t0, -24(fp)				# 10
	lw t0, -20(fp)				# 11
	lw t1, -24(fp)				# 12
	addw t2, t0, t1				# 13
	addi t1, t2, 5				# 14
	sw t1, -28(fp)				# 15
	lw t1, -28(fp)				# 16
	addi t2, t1, 0				# 17
	sw t2, -32(fp)				# 18
	lw t2, -32(fp)				# 19
	li t1, 1				# 20
	mulw t0, t2, t1				# 21
	sw t0, -36(fp)				# 22
	li t0, 100				# 23
	sw t0, -40(fp)				# 24
	lw t0, -20(fp)				# 25
	lw t1, -24(fp)				# 26
	mulw t2, t0, t1				# 27
	sw t2, -44(fp)				# 28
	li t2, 0				# 29
	sw t2, -48(fp)				# 30
	j  if.then12				# 31

if.then12:
	lw t2, -36(fp)				# 35
	sw t2, -48(fp)				# 36
	j  if.end14				# 37

if.else13:
	li t2, 999				# 32
	sw t2, -48(fp)				# 33
	j  if.end14				# 34

if.end14:
	lw t2, -48(fp)				# 38
	sw t2, -52(fp)				# 39
	j  mainRet0				# 40

mainRet0:
	lw t2, -52(fp)				# 41
	addi a0, t2, 0				# 42
	ld s1, 0(sp)
	addi sp, sp, 96				# 43
	ld ra, -8(sp)				# 44
	ld fp, -16(sp)				# 45
	jr ra					# 46

