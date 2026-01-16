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
	sw t0, -24(fp)				# 6
	li t0, 0				# 7
	sw t0, -20(fp)				# 8
	li t0, 0				# 9
	sw t0, -28(fp)				# 10
	j  whileCond6				# 11

whileCond6:
	lw t0, -20(fp)				# 12
	li t1, 10000000				# 13
	slt t2, t0, t1				# 14
	andi t1, t2, 1				# 15
	xori t2, t1, 0				# 16
	sltu t1, zero, t2				# 17
	bne t1, zero, doWhileBody7				# 18
	j  whileNext9				# 19

doWhileBody7:
	lw t1, -28(fp)				# 20
	lw t2, -20(fp)				# 21
	addw t0, t1, t2				# 22
	sw t0, -28(fp)				# 23
	lw t0, -20(fp)				# 24
	addi t2, t0, 1				# 25
	sw t2, -20(fp)				# 26
	j  doWhileCond8				# 27

doWhileCond8:
	lw t2, -20(fp)				# 28
	li t0, 10000000				# 29
	slt t1, t2, t0				# 30
	andi t0, t1, 1				# 31
	xori t1, t0, 0				# 32
	sltu t0, zero, t1				# 33
	bne t0, zero, doWhileBody7				# 34
	j  whileNext9				# 35

whileNext9:
	lw t0, -28(fp)				# 36
	sw t0, -24(fp)				# 37
	j  mainRet0				# 38

mainRet0:
	lw t0, -24(fp)				# 39
	addi a0, t0, 0				# 40
	ld s1, 0(sp)
	addi sp, sp, 64				# 41
	ld ra, -8(sp)				# 42
	ld fp, -16(sp)				# 43
	jr ra					# 44

