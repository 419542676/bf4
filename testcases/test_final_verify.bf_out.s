.globl	main
main:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -96				# 3
	sd s1, 0(sp)
	j  if.then10				# 4

if.then10:
	j  if.end12				# 5

if.end12:
	j  whileCond13				# 6

whileCond13:
	j  doWhileBody14				# 7

doWhileBody14:
	addi t4, t0, 200				# 8
	li t5, 5				# 9
	slt t6, t3, t5				# 10
	andi t5, t6, 1				# 11
	xori t6, t5, 0				# 12
	sltu t5, zero, t6				# 13
	bne t5, zero, if.then19				# 14
	j  if.else20				# 15

if.then19:
	addi t5, t4, 1				# 18
	j  if.end21				# 19

if.else20:
	addi t5, t4, 2				# 16
	j  if.end21				# 17

if.end21:
	addi t5, t3, 1				# 20
	j  doWhileCond15				# 21

doWhileCond15:
	li t4, 10				# 22
	slt t6, t5, t4				# 23
	andi t4, t6, 1				# 24
	xori t6, t4, 0				# 25
	sltu t4, zero, t6				# 26
	bne t4, zero, doWhileBody14				# 27
	j  whileNext16				# 28

whileNext16:
	addw t3, t2, t1				# 29
	li t2, -2100				# 30
	add t1, t3, t2				# 31
	j  mainRet0				# 32

mainRet0:
	addi a0, t1, 0				# 33
	ld s1, 0(sp)
	addi sp, sp, 96				# 34
	ld ra, -8(sp)				# 35
	ld fp, -16(sp)				# 36
	jr ra					# 37

