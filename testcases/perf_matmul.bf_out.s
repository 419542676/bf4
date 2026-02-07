.globl	main
main:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -224				# 3
	sd s1, 0(sp)
	sd s2, 8(sp)
	sd s3, 16(sp)
	sd s4, 24(sp)
	sd s5, 32(sp)
	sd s6, 40(sp)
	j  whileCond8				# 4

whileCond8:
	andi t1, t0, 1				# 5
	xori t2, t1, 0				# 6
	sltu t1, zero, t2				# 7
	li t2, 0				# 8
	sw t2, -48(fp)				# 9
	bne t1, zero, doWhileBody9				# 10
	j  whileNext11				# 11

doWhileBody9:
	lw t1, -48(fp)				# 12
	la t2, A				# 13
	slliw t3, t1, 2				# 14
	add t4, t2, t3				# 15
	li t3, 10				# 16
	remw t2, t1, t3				# 17
	sw t2, 0(t4)				# 18
	la t4, B				# 19
	slliw t2, t1, 2				# 20
	add t3, t4, t2				# 21
	li t2, 5				# 22
	remw t4, t1, t2				# 23
	sw t4, 0(t3)				# 24
	addi t4, t1, 1				# 25
	j  doWhileCond10				# 26

doWhileCond10:
	li t1, 400				# 27
	slt t3, t4, t1				# 28
	andi t1, t3, 1				# 29
	xori t3, t1, 0				# 30
	sltu t1, zero, t3				# 31
	sw t4, -48(fp)				# 32
	bne t1, zero, doWhileBody9				# 33
	j  whileNext11				# 34

whileNext11:
	j  whileCond12				# 35

whileCond12:
	andi t1, t0, 1				# 36
	xori t4, t1, 0				# 37
	sltu t1, zero, t4				# 38
	li t4, 0				# 39
	sw t4, -56(fp)				# 40
	li t4, 0				# 41
	sw t4, -60(fp)				# 42
	bne t1, zero, doWhileBody13				# 43
	j  whileNext15				# 44

doWhileBody13:
	lw t1, -52(fp)				# 45
	lw t4, -56(fp)				# 46
	lw t3, -60(fp)				# 47
	lw t2, -64(fp)				# 48
	lw t5, -68(fp)				# 49
	lw t6, -72(fp)				# 50
	j  whileCond16				# 51

whileCond16:
	andi s1, t0, 1				# 52
	xori s2, s1, 0				# 53
	sltu s1, zero, s2				# 54
	li s2, 0				# 55
	sw s2, -76(fp)				# 56
	sw t5, -80(fp)				# 57
	sw t6, -84(fp)				# 58
	sw t1, -112(fp)				# 59
	li t1, 0				# 60
	sw t1, -116(fp)				# 61
	sw t3, -120(fp)				# 62
	sw t2, -124(fp)				# 63
	sw t5, -128(fp)				# 64
	sw t6, -132(fp)				# 65
	bne s1, zero, loop_preheader_165				# 66
	j  whileNext19				# 67

loop_preheader_165:
	li s1, 20				# 68
	mulw t6, t4, s1				# 69
	j  doWhileBody17				# 70

doWhileBody17:
	lw s1, -76(fp)				# 71
	lw t5, -80(fp)				# 72
	lw t2, -84(fp)				# 73
	j  whileCond21				# 74

whileCond21:
	andi t3, t0, 1				# 75
	xori t1, t3, 0				# 76
	sltu t3, zero, t1				# 77
	li t1, 0				# 78
	sw t1, -88(fp)				# 79
	li t1, 0				# 80
	sw t1, -92(fp)				# 81
	li t1, 0				# 82
	sw t1, -96(fp)				# 83
	li t1, 0				# 84
	sw t1, -100(fp)				# 85
	sw t5, -104(fp)				# 86
	sw t2, -108(fp)				# 87
	bne t3, zero, loop_preheader_064				# 88
	j  whileNext24				# 89

loop_preheader_064:
	li t3, 20				# 90
	mulw t2, t4, t3				# 91
	j  doWhileBody22				# 92

doWhileBody22:
	lw t3, -88(fp)				# 93
	lw t5, -92(fp)				# 94
	addw t1, t2, t3				# 95
	li s2, 20				# 96
	mulw s3, t3, s2				# 97
	addw s2, s3, s1				# 98
	la s3, A				# 99
	slliw s4, t1, 2				# 100
	add s5, s3, s4				# 101
	lw s4, 0(s5)				# 102
	la s5, B				# 103
	slliw s3, s2, 2				# 104
	add s6, s5, s3				# 105
	lw s3, 0(s6)				# 106
	mulw s6, s4, s3				# 107
	addw s3, t5, s6				# 108
	addi t5, t3, 1				# 109
	j  doWhileCond23				# 110

doWhileCond23:
	li t3, 20				# 111
	slt s6, t5, t3				# 112
	andi t3, s6, 1				# 113
	xori s6, t3, 0				# 114
	sltu t3, zero, s6				# 115
	sw t5, -88(fp)				# 116
	sw s3, -92(fp)				# 117
	sw t5, -96(fp)				# 118
	sw s3, -100(fp)				# 119
	sw t1, -104(fp)				# 120
	sw s2, -108(fp)				# 121
	bne t3, zero, doWhileBody22				# 122
	j  whileNext24				# 123

whileNext24:
	lw t2, -96(fp)				# 124
	lw t3, -100(fp)				# 125
	lw s2, -104(fp)				# 126
	lw t1, -108(fp)				# 127
	addw s3, t6, s1				# 128
	la t5, C				# 129
	slliw s6, s3, 2				# 130
	add s4, t5, s6				# 131
	sw t3, 0(s4)				# 132
	addi s4, s1, 1				# 133
	j  doWhileCond18				# 134

doWhileCond18:
	li s1, 20				# 135
	slt s6, s4, s1				# 136
	andi s1, s6, 1				# 137
	xori s6, s1, 0				# 138
	sltu s1, zero, s6				# 139
	sw s4, -76(fp)				# 140
	sw s2, -80(fp)				# 141
	sw t1, -84(fp)				# 142
	sw s3, -112(fp)				# 143
	sw s4, -116(fp)				# 144
	sw t2, -120(fp)				# 145
	sw t3, -124(fp)				# 146
	sw s2, -128(fp)				# 147
	sw t1, -132(fp)				# 148
	bne s1, zero, doWhileBody17				# 149
	j  whileNext19				# 150

whileNext19:
	lw t6, -112(fp)				# 151
	lw s1, -116(fp)				# 152
	lw s1, -120(fp)				# 153
	lw t1, -124(fp)				# 154
	lw s2, -128(fp)				# 155
	lw t3, -132(fp)				# 156
	addi t2, t4, 1				# 157
	j  doWhileCond14				# 158

doWhileCond14:
	li t4, 20				# 159
	slt s4, t2, t4				# 160
	andi t4, s4, 1				# 161
	xori s4, t4, 0				# 162
	sltu t4, zero, s4				# 163
	sw t6, -52(fp)				# 164
	sw t2, -56(fp)				# 165
	sw s1, -60(fp)				# 166
	sw t1, -64(fp)				# 167
	sw s2, -68(fp)				# 168
	sw t3, -72(fp)				# 169
	bne t4, zero, doWhileBody13				# 170
	j  whileNext15				# 171

whileNext15:
	la t0, C				# 172
	addi t4, t0, 840				# 173
	lw t0, 0(t4)				# 174
	j  mainRet0				# 175

mainRet0:
	addi a0, t0, 0				# 176
	ld s1, 0(sp)
	ld s2, 8(sp)
	ld s3, 16(sp)
	ld s4, 24(sp)
	ld s5, 32(sp)
	ld s6, 40(sp)
	addi sp, sp, 224				# 177
	ld ra, -8(sp)				# 178
	ld fp, -16(sp)				# 179
	jr ra					# 180

.data
A:
	.zero	1600
.data
B:
	.zero	1600
.data
C:
	.zero	1600
