.globl	main
main:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -96				# 3
	sd s1, 0(sp)
	j  mainEntry14				# 4

mainEntry14:
	li t0, 0				# 5
	sw t0, -60(fp)				# 6
	li t0, 5				# 7
	sw t0, -20(fp)				# 8
	li t0, 20				# 9
	sw t0, -44(fp)				# 10
	addi t0, fp, -40				# 11
	addi t0, t0, 0				# 12
	li t1, 1				# 13
	sw t1, 0(t0)				# 14
	addi t1, fp, -40				# 15
	addi t1, t1, 4				# 16
	li t0, 2				# 17
	sw t0, 0(t1)				# 18
	lw t0, -20(fp)				# 19
	la t1, g_val				# 20
	lw t2, 0(t1)				# 21
	addw t1, t0, t2				# 22
	sw t1, -64(fp)				# 23
	lw t1, -64(fp)				# 24
	li t2, 20				# 25
	slt t0, t2, t1				# 26
	andi t2, t0, 1				# 27
	xori t0, t2, 0				# 28
	sltu t2, zero, t0				# 29
	bne t2, zero, if.then20				# 30
	j  if.else21				# 31

if.then20:
	lw t1, -64(fp)				# 37
	addi t0, t1, -5				# 38
	sw t0, -64(fp)				# 39
	j  if.end22				# 40

if.else21:
	lw t2, -64(fp)				# 32
	lw t0, -44(fp)				# 33
	addw t1, t2, t0				# 34
	sw t1, -64(fp)				# 35
	j  if.end22				# 36

if.end22:
	li t0, 0				# 41
	sw t0, -52(fp)				# 42
	j  whileCond24				# 43

whileCond24:
	lw t0, -52(fp)				# 44
	li t1, 3				# 45
	slt t2, t0, t1				# 46
	andi t1, t2, 1				# 47
	xori t2, t1, 0				# 48
	sltu t1, zero, t2				# 49
	bne t1, zero, doWhileBody25				# 50
	j  whileNext27				# 51

doWhileBody25:
	lw t1, -64(fp)				# 52
	addi t2, t1, -2				# 53
	sw t2, -64(fp)				# 54
	lw t2, -52(fp)				# 55
	addi t1, t2, 1				# 56
	sw t1, -52(fp)				# 57
	j  doWhileCond26				# 58

doWhileCond26:
	lw t1, -52(fp)				# 59
	li t2, 3				# 60
	slt t0, t1, t2				# 61
	andi t2, t0, 1				# 62
	xori t0, t2, 0				# 63
	sltu t2, zero, t0				# 64
	bne t2, zero, doWhileBody25				# 65
	j  whileNext27				# 66

whileNext27:
	lw t2, -20(fp)				# 67
	addi a0, t2, 0				# 68
	addi a1, zero, 4				# 69
	addi sp, sp, -32
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
	jal ra, multiply_helper				# 70
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	addi sp, sp, 32
	addi t2, a0, 0				# 71
	sw t2, -56(fp)				# 72
	lw t2, -64(fp)				# 73
	lw t0, -56(fp)				# 74
	addw t1, t2, t0				# 75
	addi t0, fp, -40				# 76
	addi t0, t0, 0				# 77
	lw t2, 0(t0)				# 78
	addw t0, t1, t2				# 79
	addi t2, t0, 5				# 80
	sw t2, -48(fp)				# 81
	lw t2, -48(fp)				# 82
	sw t2, -60(fp)				# 83
	j  mainRet12				# 84

mainRet12:
	lw t2, -60(fp)				# 85
	addi a0, t2, 0				# 86
	ld s1, 0(sp)
	addi sp, sp, 96				# 87
	ld ra, -8(sp)				# 88
	ld fp, -16(sp)				# 89
	jr ra					# 90

multiply_helper:
	sd ra, -8(sp)				# 91
	sd fp, -16(sp)				# 92
	add fp, sp, zero				# 93
	addi sp, sp, -80				# 94
	sd s1, 0(sp)
	addi t0, a0, 0				# 95
	addi t1, a1, 0				# 96
	j  multiply_helperEntry2				# 97

multiply_helperEntry2:
	li t2, 0				# 98
	sw t2, -32(fp)				# 99
	sw t0, -36(fp)				# 100
	sw t1, -24(fp)				# 101
	li t1, 0				# 102
	sw t1, -28(fp)				# 103
	li t1, 0				# 104
	sw t1, -20(fp)				# 105
	j  whileCond8				# 106

whileCond8:
	lw t1, -20(fp)				# 107
	lw t0, -24(fp)				# 108
	slt t2, t1, t0				# 109
	andi t0, t2, 1				# 110
	xori t2, t0, 0				# 111
	sltu t0, zero, t2				# 112
	bne t0, zero, doWhileBody9				# 113
	j  whileNext11				# 114

doWhileBody9:
	lw t0, -28(fp)				# 115
	lw t2, -36(fp)				# 116
	addw t1, t0, t2				# 117
	sw t1, -28(fp)				# 118
	lw t1, -20(fp)				# 119
	addi t2, t1, 1				# 120
	sw t2, -20(fp)				# 121
	j  doWhileCond10				# 122

doWhileCond10:
	lw t2, -20(fp)				# 123
	lw t1, -24(fp)				# 124
	slt t0, t2, t1				# 125
	andi t1, t0, 1				# 126
	xori t0, t1, 0				# 127
	sltu t1, zero, t0				# 128
	bne t1, zero, doWhileBody9				# 129
	j  whileNext11				# 130

whileNext11:
	lw t1, -28(fp)				# 131
	sw t1, -32(fp)				# 132
	j  multiply_helperRet0				# 133

multiply_helperRet0:
	lw t1, -32(fp)				# 134
	addi a0, t1, 0				# 135
	ld s1, 0(sp)
	addi sp, sp, 80				# 136
	ld ra, -8(sp)				# 137
	ld fp, -16(sp)				# 138
	jr ra					# 139

.data
g_val:
	.word	10
.data
g_step:
	.word	2
