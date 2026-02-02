.global _start
_start:
	li t0, 1 # t0 <- 1
	li s1, 0 # s1 <- 0
	li t2, 30 # t2 <- 30, for comparison
	
loop: 
	add s1, s1, t0 # s1 += t0, sum up
	addi t0, t0, 1 # t0++, add 1 each loop
	ble t0, t2, loop # only end loop if t0>30
	
iloop:
	j iloop # infinite loop
	
	