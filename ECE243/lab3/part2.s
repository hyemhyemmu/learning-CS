.global _start
_start:

	la t0, InputWord # t0 <- addr of inputword
	lw a0, (t0) # t1 <- inputword number
	
	call ONES # call subroutine
	
	la t1, Answer # load the address of Answer
	sw a0, (t1) # store answer into Answer
	
stop: j stop

ONES:
	li t2, 0 # t2 as a counter
	li t3, 0 # t3 as mask result
	
counting:
	beq a0, zero, end # end loop if a0 is already 0
	andi t3, a0, 1 # AND operation at the lowest number, result store in t3
	add t2, t2, t3 # add this loop's result on counter
	srli a0, a0, 1 # t1 shift right 1 bit
	j counting
	
end:
	mv a0, t2 # move the result back to a0
	ret # return to main


.data
InputWord: .word 0x4a01fead
Answer: .word 0
	
	