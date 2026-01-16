.globl	main
collatz:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -64				# 3
	sd s1, 0(sp)
	addi t0, a0, 0				# 4
	j  collatzEntry2				# 5

collatzEntry2:
	li t1, 0				# 6
	sw t1, -24(fp)				# 7
	sw t0, -20(fp)				# 8
	li t0, 0				# 9
	sw t0, -28(fp)				# 10
	j  whileCond6				# 11

whileCond6:
	lw t0, -20(fp)				# 12
	xori t1, t0, 1				# 13
	sltu t0, zero, t1				# 14
	andi t1, t0, 1				# 15
	xori t0, t1, 0				# 16
	sltu t1, zero, t0				# 17
	bne t1, zero, doWhileBody7				# 18
	j  whileNext9				# 19

doWhileBody7:
	lw t1, -20(fp)				# 20
	li t0, 2				# 21
	remw t2, t1, t0				# 22
	xori t0, t2, 0				# 23
	sltu t2, zero, t0				# 24
	xori t2, t2, 1				# 25
	andi t0, t2, 1				# 26
	xori t2, t0, 0				# 27
	sltu t0, zero, t2				# 28
	bne t0, zero, if.then10				# 29
	j  if.else11				# 30

if.then10:
	lw t2, -20(fp)				# 37
	li t1, 2				# 38
	divw t0, t2, t1				# 39
	sw t0, -20(fp)				# 40
	j  if.end12				# 41

if.else11:
	lw t0, -20(fp)				# 31
	li t2, 3				# 32
	mulw t1, t2, t0				# 33
	addi t2, t1, 1				# 34
	sw t2, -20(fp)				# 35
	j  if.end12				# 36

if.end12:
	lw t0, -28(fp)				# 42
	addi t1, t0, 1				# 43
	sw t1, -28(fp)				# 44
	j  doWhileCond8				# 45

doWhileCond8:
	lw t1, -20(fp)				# 46
	xori t0, t1, 1				# 47
	sltu t1, zero, t0				# 48
	andi t0, t1, 1				# 49
	xori t1, t0, 0				# 50
	sltu t0, zero, t1				# 51
	bne t0, zero, doWhileBody7				# 52
	j  whileNext9				# 53

whileNext9:
	lw t0, -28(fp)				# 54
	sw t0, -24(fp)				# 55
	j  collatzRet0				# 56

collatzRet0:
	lw t0, -24(fp)				# 57
	addi a0, t0, 0				# 58
	ld s1, 0(sp)
	addi sp, sp, 64				# 59
	ld ra, -8(sp)				# 60
	ld fp, -16(sp)				# 61
	jr ra					# 62

main:
	sd ra, -8(sp)				# 63
	sd fp, -16(sp)				# 64
	add fp, sp, zero				# 65
	addi sp, sp, -64				# 66
	sd s1, 0(sp)
	j  mainEntry15				# 67

mainEntry15:
	li t0, 0				# 68
	sw t0, -24(fp)				# 69
	li t0, 1				# 70
	sw t0, -20(fp)				# 71
	li t0, 0				# 72
	sw t0, -28(fp)				# 73
	j  whileCond19				# 74

whileCond19:
	lw t0, -20(fp)				# 75
	li t1, 1000				# 76
	slt t2, t0, t1				# 77
	andi t1, t2, 1				# 78
	xori t2, t1, 0				# 79
	sltu t1, zero, t2				# 80
	bne t1, zero, doWhileBody20				# 81
	j  whileNext22				# 82

doWhileBody20:
	lw t1, -28(fp)				# 83
	lw t2, -20(fp)				# 84
	addi a0, t2, 0				# 85
	addi sp, sp, -32
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
	jal ra, collatz				# 86
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	addi sp, sp, 32
	addi t2, a0, 0				# 87
	addw t0, t1, t2				# 88
	sw t0, -28(fp)				# 89
	lw t0, -20(fp)				# 90
	addi t2, t0, 1				# 91
	sw t2, -20(fp)				# 92
	j  doWhileCond21				# 93

doWhileCond21:
	lw t2, -20(fp)				# 94
	li t0, 1000				# 95
	slt t1, t2, t0				# 96
	andi t0, t1, 1				# 97
	xori t1, t0, 0				# 98
	sltu t0, zero, t1				# 99
	bne t0, zero, doWhileBody20				# 100
	j  whileNext22				# 101

whileNext22:
	lw t0, -28(fp)				# 102
	sw t0, -24(fp)				# 103
	j  mainRet13				# 104

mainRet13:
	lw t0, -24(fp)				# 105
	addi a0, t0, 0				# 106
	ld s1, 0(sp)
	addi sp, sp, 64				# 107
	ld ra, -8(sp)				# 108
	ld fp, -16(sp)				# 109
	jr ra					# 110

