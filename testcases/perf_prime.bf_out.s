.globl	main
is_prime:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -80				# 3
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
	li t0, 0				# 54
	sw t0, -36(fp)				# 55
	j  is_primeRet0				# 56

if.end6:
	j  whileCond8				# 12

whileCond8:
	li t1, 4				# 13
	slt t2, t0, t1				# 14
	xori t2, t2, 1				# 15
	andi t1, t2, 1				# 16
	xori t2, t1, 0				# 17
	sltu t1, zero, t2				# 18
	li t2, 2				# 19
	sw t2, -28(fp)				# 20
	li t2, 2				# 21
	sw t2, -32(fp)				# 22
	bne t1, zero, doWhileBody9				# 23
	j  whileNext11				# 24

doWhileBody9:
	lw t1, -28(fp)				# 25
	remw t2, t0, t1				# 26
	xori t3, t2, 0				# 27
	sltu t2, zero, t3				# 28
	xori t2, t2, 1				# 29
	andi t3, t2, 1				# 30
	xori t2, t3, 0				# 31
	sltu t3, zero, t2				# 32
	bne t3, zero, if.then12				# 33
	j  if.end13				# 34

if.then12:
	li t0, 0				# 51
	sw t0, -36(fp)				# 52
	j  is_primeRet0				# 53

if.end13:
	addi t3, t1, 1				# 35
	j  doWhileCond10				# 36

doWhileCond10:
	mulw t1, t3, t3				# 37
	slt t2, t0, t1				# 38
	xori t2, t2, 1				# 39
	andi t1, t2, 1				# 40
	xori t2, t1, 0				# 41
	sltu t1, zero, t2				# 42
	sw t3, -28(fp)				# 43
	sw t3, -32(fp)				# 44
	bne t1, zero, doWhileBody9				# 45
	j  whileNext11				# 46

whileNext11:
	lw t0, -32(fp)				# 47
	li t0, 1				# 48
	sw t0, -36(fp)				# 49
	j  is_primeRet0				# 50

is_primeRet0:
	lw t0, -36(fp)				# 57
	addi a0, t0, 0				# 58
	ld s1, 0(sp)
	addi sp, sp, 80				# 59
	ld ra, -8(sp)				# 60
	ld fp, -16(sp)				# 61
	jr ra					# 62

main:
	sd ra, -8(sp)				# 63
	sd fp, -16(sp)				# 64
	add fp, sp, zero				# 65
	addi sp, sp, -80				# 66
	sd s1, 0(sp)
	j  whileCond20				# 67

whileCond20:
	andi t1, t0, 1				# 68
	xori t0, t1, 0				# 69
	sltu t1, zero, t0				# 70
	li t0, 0				# 71
	sw t0, -24(fp)				# 72
	li t0, 0				# 73
	sw t0, -28(fp)				# 74
	li t0, 0				# 75
	sw t0, -36(fp)				# 76
	bne t1, zero, doWhileBody21				# 77
	j  whileNext23				# 78

doWhileBody21:
	lw t1, -24(fp)				# 79
	lw t0, -28(fp)				# 80
	addi a0, t0, 0				# 81
	addi sp, sp, -32
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
	sd t3, 24(sp)
	jal ra, is_prime				# 82
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	ld t3, 24(sp)
	addi sp, sp, 32
	addi t2, a0, 0				# 83
	xori t3, t2, 0				# 84
	sltu t2, zero, t3				# 85
	sw t1, -32(fp)				# 86
	bne t2, zero, if.then24				# 87
	j  if.end25				# 88

if.then24:
	addi t2, t1, 1				# 89
	sw t2, -32(fp)				# 90
	j  if.end25				# 91

if.end25:
	lw t2, -32(fp)				# 92
	addi t1, t0, 1				# 93
	j  doWhileCond22				# 94

doWhileCond22:
	li t0, 50000				# 95
	slt t3, t1, t0				# 96
	andi t0, t3, 1				# 97
	xori t3, t0, 0				# 98
	sltu t0, zero, t3				# 99
	sw t2, -24(fp)				# 100
	sw t1, -28(fp)				# 101
	sw t2, -36(fp)				# 102
	bne t0, zero, doWhileBody21				# 103
	j  whileNext23				# 104

whileNext23:
	lw t0, -36(fp)				# 105
	j  mainRet14				# 106

mainRet14:
	addi a0, t0, 0				# 107
	ld s1, 0(sp)
	addi sp, sp, 80				# 108
	ld ra, -8(sp)				# 109
	ld fp, -16(sp)				# 110
	jr ra					# 111

