.global _start
_start:

	la t0, InputWord # t0 <- addr of inputword ?
	lw t1, (t0) # t1 <- inputword number
	
	li t2, 0 # temp result
	li t3, 0 # t3 as a counter
	
counting:
	beq t1, zero, end # end loop if t1 is already 0
	andi t2, t1, 1 # AND operation at the lowest number, result store in t2
	add t3, t3, t2 # add this loop's result on counter
	srli t1, t1, 1 # t1 shift right 1 bit
	j counting
	
end:
	la t4, Answer # load the address of Answer
	sw t3, (t4) # store answer into Answer

stop: j stop

.data
InputWord: .word 0x4a01fead
Answer: .word 0
	
	