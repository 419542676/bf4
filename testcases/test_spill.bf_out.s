.globl	main
main:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -128				# 3
	sd s1, 0(sp)
	j  mainEntry2				# 4

mainEntry2:
	li t0, 0				# 5
	sw t0, -80(fp)				# 6
	li t0, 1				# 7
	sw t0, -20(fp)				# 8
	li t0, 2				# 9
	sw t0, -24(fp)				# 10
	li t0, 3				# 11
	sw t0, -28(fp)				# 12
	li t0, 4				# 13
	sw t0, -32(fp)				# 14
	li t0, 5				# 15
	sw t0, -36(fp)				# 16
	li t0, 6				# 17
	sw t0, -40(fp)				# 18
	li t0, 7				# 19
	sw t0, -44(fp)				# 20
	li t0, 8				# 21
	sw t0, -48(fp)				# 22
	li t0, 9				# 23
	sw t0, -52(fp)				# 24
	li t0, 10				# 25
	sw t0, -56(fp)				# 26
	li t0, 11				# 27
	sw t0, -60(fp)				# 28
	li t0, 12				# 29
	sw t0, -64(fp)				# 30
	li t0, 13				# 31
	sw t0, -68(fp)				# 32
	li t0, 14				# 33
	sw t0, -72(fp)				# 34
	li t0, 15				# 35
	sw t0, -76(fp)				# 36
	li t0, 0				# 37
	sw t0, -84(fp)				# 38
	li t0, 0				# 39
	sw t0, -88(fp)				# 40
	j  whileCond21				# 41

whileCond21:
	lw t0, -88(fp)				# 42
	li t1, 10000000				# 43
	slt t2, t0, t1				# 44
	andi t1, t2, 1				# 45
	xori t2, t1, 0				# 46
	sltu t1, zero, t2				# 47
	bne t1, zero, doWhileBody22				# 48
	j  whileNext24				# 49

doWhileBody22:
	lw t1, -20(fp)				# 50
	lw t2, -24(fp)				# 51
	addw t0, t1, t2				# 52
	lw t2, -28(fp)				# 53
	mulw t1, t0, t2				# 54
	lw t2, -32(fp)				# 55
	lw t0, -36(fp)				# 56
	addw t3, t2, t0				# 57
	lw t2, -40(fp)				# 58
	mulw t0, t3, t2				# 59
	addw t2, t1, t0				# 60
	lw t1, -44(fp)				# 61
	lw t0, -48(fp)				# 62
	addw t3, t1, t0				# 63
	lw t0, -52(fp)				# 64
	mulw t1, t3, t0				# 65
	addw t0, t2, t1				# 66
	lw t1, -56(fp)				# 67
	lw t2, -60(fp)				# 68
	addw t3, t1, t2				# 69
	lw t2, -64(fp)				# 70
	mulw t1, t3, t2				# 71
	addw t2, t0, t1				# 72
	lw t1, -68(fp)				# 73
	lw t0, -72(fp)				# 74
	addw t3, t1, t0				# 75
	lw t0, -76(fp)				# 76
	mulw t1, t3, t0				# 77
	addw t0, t2, t1				# 78
	sw t0, -84(fp)				# 79
	lw t0, -20(fp)				# 80
	addi t1, t0, 1				# 81
	sw t1, -20(fp)				# 82
	lw t1, -24(fp)				# 83
	addi t0, t1, 1				# 84
	sw t0, -24(fp)				# 85
	lw t0, -20(fp)				# 86
	li t1, 3				# 87
	remw t2, t0, t1				# 88
	sw t2, -20(fp)				# 89
	lw t2, -24(fp)				# 90
	li t1, 3				# 91
	remw t0, t2, t1				# 92
	sw t0, -24(fp)				# 93
	lw t0, -88(fp)				# 94
	addi t1, t0, 1				# 95
	sw t1, -88(fp)				# 96
	j  doWhileCond23				# 97

doWhileCond23:
	lw t1, -88(fp)				# 98
	li t0, 10000000				# 99
	slt t2, t1, t0				# 100
	andi t0, t2, 1				# 101
	xori t2, t0, 0				# 102
	sltu t0, zero, t2				# 103
	bne t0, zero, doWhileBody22				# 104
	j  whileNext24				# 105

whileNext24:
	lw t0, -84(fp)				# 106
	li t2, 0				# 107
	slt t1, t2, t0				# 108
	andi t2, t1, 1				# 109
	xori t1, t2, 0				# 110
	sltu t2, zero, t1				# 111
	bne t2, zero, if.then25				# 112
	j  if.end26				# 113

if.then25:
	li t2, 1				# 117
	sw t2, -80(fp)				# 118
	j  mainRet0				# 119

if.end26:
	li t2, 0				# 114
	sw t2, -80(fp)				# 115
	j  mainRet0				# 116

mainRet0:
	lw t2, -80(fp)				# 120
	addi a0, t2, 0				# 121
	ld s1, 0(sp)
	addi sp, sp, 128				# 122
	ld ra, -8(sp)				# 123
	ld fp, -16(sp)				# 124
	jr ra					# 125

