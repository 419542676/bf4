.globl	main
main:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -112				# 3
	sd s1, 0(sp)
	j  if.then10				# 4

if.then10:
	li t1, 100				# 8
	sw t1, -48(fp)				# 9
	j  if.end12				# 10

if.else11:
	li t1, 999				# 5
	sw t1, -48(fp)				# 6
	j  if.end12				# 7

if.end12:
	lw t1, -48(fp)				# 11
	j  whileCond13				# 12

whileCond13:
	andi t2, t0, 1				# 13
	xori t0, t2, 0				# 14
	sltu t2, zero, t0				# 15
	li t0, 0				# 16
	sw t0, -52(fp)				# 17
	li t0, 0				# 18
	sw t0, -56(fp)				# 19
	li t0, 0				# 20
	sw t0, -64(fp)				# 21
	bne t2, zero, doWhileBody14				# 22
	j  whileNext16				# 23

doWhileBody14:
	lw t2, -52(fp)				# 24
	lw t0, -56(fp)				# 25
	addi t3, t2, 200				# 26
	li t2, 5				# 27
	slt t4, t0, t2				# 28
	andi t2, t4, 1				# 29
	xori t4, t2, 0				# 30
	sltu t2, zero, t4				# 31
	bne t2, zero, if.then19				# 32
	j  if.else20				# 33

if.then19:
	addi t2, t3, 1				# 37
	sw t2, -60(fp)				# 38
	j  if.end21				# 39

if.else20:
	addi t2, t3, 2				# 34
	sw t2, -60(fp)				# 35
	j  if.end21				# 36

if.end21:
	lw t2, -60(fp)				# 40
	addi t3, t0, 1				# 41
	j  doWhileCond15				# 42

doWhileCond15:
	li t0, 10				# 43
	slt t4, t3, t0				# 44
	andi t0, t4, 1				# 45
	xori t4, t0, 0				# 46
	sltu t0, zero, t4				# 47
	sw t2, -52(fp)				# 48
	sw t3, -56(fp)				# 49
	sw t2, -64(fp)				# 50
	bne t0, zero, doWhileBody14				# 51
	j  whileNext16				# 52

whileNext16:
	lw t0, -64(fp)				# 53
	addw t2, t1, t0				# 54
	li t1, -2100				# 55
	add t0, t2, t1				# 56
	j  mainRet0				# 57

mainRet0:
	addi a0, t0, 0				# 58
	ld s1, 0(sp)
	addi sp, sp, 112				# 59
	ld ra, -8(sp)				# 60
	ld fp, -16(sp)				# 61
	jr ra					# 62

