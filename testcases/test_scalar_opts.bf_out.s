.globl	main
get_hidden_val:
	sd ra, -8(sp)				# 0
	sd fp, -16(sp)				# 1
	add fp, sp, zero				# 2
	addi sp, sp, -64				# 3
	sd s1, 0(sp)
	j  get_hidden_valRet0				# 4

get_hidden_valRet0:
	addi a0, zero, 10				# 5
	ld s1, 0(sp)
	addi sp, sp, 64				# 6
	ld ra, -8(sp)				# 7
	ld fp, -16(sp)				# 8
	jr ra					# 9

main:
	sd ra, -8(sp)				# 10
	sd fp, -16(sp)				# 11
	add fp, sp, zero				# 12
	addi sp, sp, -96				# 13
	sd s1, 0(sp)
	addi sp, sp, -16
	sd t0, 0(sp)
	sd t1, 8(sp)
	jal ra, get_hidden_val				# 14
	ld t0, 0(sp)
	ld t1, 8(sp)
	addi sp, sp, 16
	addi t0, a0, 0				# 15
	addi t1, t0, 60				# 16
	j  mainRet4				# 17

mainRet4:
	addi a0, t1, 0				# 18
	ld s1, 0(sp)
	addi sp, sp, 96				# 19
	ld ra, -8(sp)				# 20
	ld fp, -16(sp)				# 21
	jr ra					# 22

