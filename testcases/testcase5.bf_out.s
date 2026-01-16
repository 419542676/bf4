.globl	main
doWork:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -64				# 3
	sd s1, 0(sp)
	j  doWorkEntry2				# 4

doWorkEntry2:
	li t0, 0				# 5
	sw t0, -24(fp)				# 6
	li t0, 0				# 7
	sw t0, -20(fp)				# 8
	j  whileCond5				# 9

whileCond5:
	lw t0, -20(fp)				# 10
	li t1, 5				# 11
	slt t2, t0, t1				# 12
	andi t1, t2, 1				# 13
	xori t2, t1, 0				# 14
	sltu t1, zero, t2				# 15
	bne t1, zero, doWhileBody6				# 16
	j  whileNext8				# 17

doWhileBody6:
	lw t1, -20(fp)				# 18
	addi t2, t1, 1				# 19
	sw t2, -20(fp)				# 20
	j  doWhileCond7				# 21

doWhileCond7:
	lw t2, -20(fp)				# 22
	li t1, 5				# 23
	slt t0, t2, t1				# 24
	andi t1, t0, 1				# 25
	xori t0, t1, 0				# 26
	sltu t1, zero, t0				# 27
	bne t1, zero, doWhileBody6				# 28
	j  whileNext8				# 29

whileNext8:
	lw t1, -20(fp)				# 30
	sw t1, -24(fp)				# 31
	j  doWorkRet0				# 32

doWorkRet0:
	lw t1, -24(fp)				# 33
	addi a0, t1, 0				# 34
	ld s1, 0(sp)
	addi sp, sp, 64				# 35
	ld ra, -8(sp)				# 36
	ld fp, -16(sp)				# 37
	jr ra					# 38

main:
	sd ra, -8(sp)				# 39
	sd fp, -16(sp)				# 40
	add fp, sp, zero				# 41
	addi sp, sp, -64				# 42
	sd s1, 0(sp)
	j  mainEntry11				# 43

mainEntry11:
	li t0, 0				# 44
	sw t0, -20(fp)				# 45
	addi sp, sp, -16
	sd t0, 0(sp)
	jal ra, doWork				# 46
	ld t0, 0(sp)
	addi sp, sp, 16
	addi t0, a0, 0				# 47
	sw t0, -24(fp)				# 48
	lw t0, -24(fp)				# 49
	sw t0, -20(fp)				# 50
	j  mainRet9				# 51

mainRet9:
	lw t0, -20(fp)				# 52
	addi a0, t0, 0				# 53
	ld s1, 0(sp)
	addi sp, sp, 64				# 54
	ld ra, -8(sp)				# 55
	ld fp, -16(sp)				# 56
	jr ra					# 57

