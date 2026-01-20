.globl	main
main:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -128				# 3
	sd s1, 0(sp)
	j  if.then10				# 4

if.then10:
	li t0, 100				# 5
	sw t0, -48(fp)				# 6
	j  if.end12				# 7

if.end12:
	ld t0, -52(fp)				# 8
	j  whileCond13				# 9

whileCond13:
	li t1, 0				# 10
	sw t1, -56(fp)				# 11
	li t1, 0				# 12
	sw t1, -64(fp)				# 13
	j  doWhileBody14				# 14

doWhileBody14:
	ld t1, -60(fp)				# 15
	ld t2, -68(fp)				# 16
	addi t3, t1, 200				# 17
	li t1, 5				# 18
	slt t4, t2, t1				# 19
	andi t1, t4, 1				# 20
	xori t4, t1, 0				# 21
	sltu t1, zero, t4				# 22
	bne t1, zero, if.then19				# 23
	j  if.else20				# 24

if.then19:
	addi t1, t3, 1				# 28
	sw t1, -72(fp)				# 29
	j  if.end21				# 30

if.else20:
	addi t1, t3, 2				# 25
	sw t1, -72(fp)				# 26
	j  if.end21				# 27

if.end21:
	ld t1, -76(fp)				# 31
	addi t3, t2, 1				# 32
	j  doWhileCond15				# 33

doWhileCond15:
	li t2, 10				# 34
	slt t4, t3, t2				# 35
	andi t2, t4, 1				# 36
	xori t4, t2, 0				# 37
	sltu t2, zero, t4				# 38
	sw t1, -56(fp)				# 39
	sw t3, -64(fp)				# 40
	sw t1, -80(fp)				# 41
	bne t2, zero, doWhileBody14				# 42
	j  whileNext16				# 43

whileNext16:
	ld t2, -84(fp)				# 44
	addw t1, t0, t2				# 45
	li t0, -2100				# 46
	add t2, t1, t0				# 47
	j  mainRet0				# 48

mainRet0:
	addi a0, t2, 0				# 49
	ld s1, 0(sp)
	addi sp, sp, 128				# 50
	ld ra, -8(sp)				# 51
	ld fp, -16(sp)				# 52
	jr ra					# 53

