.globl	main
add:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -64				# 3
	sd s1, 0(sp)
	addi t0, a0, 0				# 4
	addi t1, a1, 0				# 5
	j  addEntry2				# 6

addEntry2:
	li t2, 0				# 7
	sw t2, -28(fp)				# 8
	sw t0, -20(fp)				# 9
	sw t1, -24(fp)				# 10
	lw t1, -20(fp)				# 11
	lw t0, -24(fp)				# 12
	addw t2, t1, t0				# 13
	sw t2, -28(fp)				# 14
	j  addRet0				# 15

addRet0:
	lw t2, -28(fp)				# 16
	addi a0, t2, 0				# 17
	ld s1, 0(sp)
	addi sp, sp, 64				# 18
	ld ra, -8(sp)				# 19
	ld fp, -16(sp)				# 20
	jr ra					# 21

main:
	sd ra, -8(sp)				# 22
	sd fp, -16(sp)				# 23
	add fp, sp, zero				# 24
	addi sp, sp, -64				# 25
	sd s1, 0(sp)
	j  mainEntry8				# 26

mainEntry8:
	li t0, 0				# 27
	sw t0, -20(fp)				# 28
	addi a0, zero, 5				# 29
	addi a1, zero, 3				# 30
	addi sp, sp, -16
	sd t0, 0(sp)
	jal ra, add				# 31
	ld t0, 0(sp)
	addi sp, sp, 16
	addi t0, a0, 0				# 32
	sw t0, -24(fp)				# 33
	lw t0, -24(fp)				# 34
	sw t0, -20(fp)				# 35
	j  mainRet6				# 36

mainRet6:
	lw t0, -20(fp)				# 37
	addi a0, t0, 0				# 38
	ld s1, 0(sp)
	addi sp, sp, 64				# 39
	ld ra, -8(sp)				# 40
	ld fp, -16(sp)				# 41
	jr ra					# 42

