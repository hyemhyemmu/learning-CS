.global _start
_start:
	la sp, 0x20000
	la t0, TEST_NUM # t0 <- addr of list of numbers
	
	li t1, 0 # t1 for largest_one
	li t2, 0 # t2 for largest_zero
	li t3, 0 # t3 for temp result
	
main_loop:
	lw a0, (t0) # a0 <- current number 
	beq a0, zero, end # if a0=0, means that we are at the end of the list
	
	# ---- deal with ones ---- 
ones_logic:	
	addi sp, sp, -4
	sw a0, (sp) # save a0 (the number we are dealing with) into stack
	
	call ONES # check for num of ones, result in a0
	
	mv t3, a0 # move the result to t3 
	lw a0, (sp) # get back a0
	addi sp, sp, 4 	
	
	# compare logic
	ble t3, t1, zeroes_logic # go to zeroes_logic straightaway if not big enough
	mv t1, t3 # update if larger
	
	# ---- deal with zeroes ---- 
zeroes_logic:
	xori a0, a0, -1 # flip all the bits of the number
	call ONES # check for num of zeroes, result in a0
	
	mv t3, a0
	# compare logic
	ble t3, t2, next_loop # go to main_loop straightaway if not big enough
	mv t2, t3 # update if larger
	
	# --- start next loop ----
next_loop:
	addi t0, t0, 4 # move the pointer forward
	j main_loop
	
	# ---- finished ----
end:
	la t3, LargestOnes
	la t4, LargestZeroes
	sw t1, (t3) # save largest_ones
	sw t2, (t4) # save largest_zeros
	
	.equ LEDs, 0xFF200000 
	la s0, LEDs
	
display_loop:
	sw t1, (s0) # load largest_ones to leds
	call DELAY
	
	sw t2, (s0) # load largest_zeros to leds
	call DELAY
	
	j display_loop
	
DELAY:
	li t5, 10000000 # parameter for delay length
		# answer to question:
		# real processor should be faster, because hardware is 
		# way faster than software simulation
delay_loop:
    addi t5, t5, -1 
    bne t5, zero, delay_loop # end looping only if finish counting
    ret

# --------------------------

ONES:
	# push stack 
	addi sp, sp, -8
	sw t0, (sp) # store t0 into stack
	sw t1, 4(sp) # store t1 into stack
	
	li t0, 0 # t0 as a counter
	li t1, 0 # t1 as mask result
	
counting:
	beq a0, zero, one_end # end loop if a0 is already 0
	andi t1, a0, 1 # AND operation at the lowest number, result store in t3
	add t0, t0, t1 # add this loop's result on counter
	srli a0, a0, 1 # a0 shift right 1 bit
	j counting
	
one_end:
	mv a0, t0 # move the result back to a0
	# pop stack
	lw t0, (sp) # get back t0 from stack
	lw t1, 4(sp) # get back t1 from stack
	addi sp, sp, 8
	
	ret # return to main
# --------------------------

.data
TEST_NUM: .word 0x4a01fead, 0xF677D671,0xDC9758D5,0xEBBD45D2,0x8059519D
	.word 0x76D8F0D2, 0xB98C9BB5, 0xD7EC3A9E, 0xD9BADC01, 0x89B377CD
	.word 0 # end of list

LargestOnes: .word 0
LargestZeroes: .word 0
	
	