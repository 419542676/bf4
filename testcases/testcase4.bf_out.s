.globl	main
main:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -64				# 3
	sd s1, 0(sp)
	j  mainEntry2				# 4

mainEntry2:
	li t0, 0				# 5
	sw t0, -20(fp)				# 6
	li t0, 5				# 7
	sw t0, -24(fp)				# 8
	li t0, 10				# 9
	sw t0, -28(fp)				# 10
	lw t0, -24(fp)				# 11
	lw t1, -28(fp)				# 12
	slt t2, t1, t0				# 13
	andi t1, t2, 1				# 14
	xori t2, t1, 0				# 15
	sltu t1, zero, t2				# 16
	bne t1, zero, if.then6				# 17
	j  if.else7				# 18

if.then6:
	lw t1, -24(fp)				# 22
	sw t1, -20(fp)				# 23
	j  mainRet0				# 24

if.else7:
	lw t1, -28(fp)				# 19
	sw t1, -20(fp)				# 20
	j  mainRet0				# 21

mainRet0:
	lw t1, -20(fp)				# 25
	addi a0, t1, 0				# 26
	ld s1, 0(sp)
	addi sp, sp, 64				# 27
	ld ra, -8(sp)				# 28
	ld fp, -16(sp)				# 29
	jr ra					# 30

