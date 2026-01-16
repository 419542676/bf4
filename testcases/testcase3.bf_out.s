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
	addi t0, fp, -36				# 7
	add a0, zero, t0				# 8
	li a1, 0				# 9
	li a2, 20				# 10
	addi sp, sp, -32
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
	jal ra, memset				# 11
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	addi sp, sp, 32
	addi t0, fp, -36				# 12
	addi t0, t0, 0				# 13
	li t1, 1				# 14
	sw t1, 0(t0)				# 15
	addi t1, fp, -36				# 16
	addi t1, t1, 4				# 17
	li t0, 2				# 18
	sw t0, 0(t1)				# 19
	addi t0, fp, -36				# 20
	addi t0, t0, 8				# 21
	li t1, 3				# 22
	sw t1, 0(t0)				# 23
	addi t1, fp, -36				# 24
	addi t1, t1, 12				# 25
	li t0, 4				# 26
	sw t0, 0(t1)				# 27
	addi t0, fp, -36				# 28
	addi t0, t0, 16				# 29
	li t1, 5				# 30
	sw t1, 0(t0)				# 31
	li t1, 0				# 32
	sw t1, -40(fp)				# 33
	j  whileCond6				# 34

whileCond6:
	lw t1, -40(fp)				# 35
	li t0, 3				# 36
	slt t2, t1, t0				# 37
	andi t0, t2, 1				# 38
	xori t2, t0, 0				# 39
	sltu t0, zero, t2				# 40
	bne t0, zero, doWhileBody7				# 41
	j  whileNext9				# 42

doWhileBody7:
	lw t0, -40(fp)				# 43
	addi t2, t0, 1				# 44
	sw t2, -40(fp)				# 45
	addi t2, fp, -36				# 46
	addi t2, t2, 12				# 47
	addi t0, fp, -36				# 48
	addi t0, t0, 12				# 49
	lw t1, 0(t0)				# 50
	addi t0, t1, 1				# 51
	sw t0, 0(t2)				# 52
	j  doWhileCond8				# 53

doWhileCond8:
	lw t0, -40(fp)				# 54
	li t2, 3				# 55
	slt t1, t0, t2				# 56
	andi t2, t1, 1				# 57
	xori t1, t2, 0				# 58
	sltu t2, zero, t1				# 59
	bne t2, zero, doWhileBody7				# 60
	j  whileNext9				# 61

whileNext9:
	addi t2, fp, -36				# 62
	addi t2, t2, 12				# 63
	lw t1, 0(t2)				# 64
	sw t1, -44(fp)				# 65
	j  mainRet0				# 66

mainRet0:
	lw t1, -44(fp)				# 67
	addi a0, t1, 0				# 68
	ld s1, 0(sp)
	addi sp, sp, 80				# 69
	ld ra, -8(sp)				# 70
	ld fp, -16(sp)				# 71
	jr ra					# 72

