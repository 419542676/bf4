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
	li t0, 10				# 7
	sw t0, -24(fp)				# 8
	la t0, .LC0				# 9
	flw ft0, 0(t0)				# 10
	fsw ft0, -28(fp)				# 11
	lw t0, -24(fp)				# 12
	sw t0, -20(fp)				# 13
	j  mainRet0				# 14

mainRet0:
	lw t0, -20(fp)				# 15
	addi a0, t0, 0				# 16
	ld s1, 0(sp)
	addi sp, sp, 64				# 17
	ld ra, -8(sp)				# 18
	ld fp, -16(sp)				# 19
	jr ra					# 20

.LC0:
	.word	1078523331
.data
a:
	.word	10
.data
b:
	.word	20
.data
c:
	.word	1078523331
.data
d:
	.word	1076753334
