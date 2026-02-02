.global _start
_start:

la s0, result # The address of the result
lw t0, 4(s0) # The number of numbers is in t0

la t1, numbers # The address of the numbers is in t1

#Keep the largest number so far in t2

    lw t2, 0(t1)

#Loop to search for the biggest number

loop: 
    addi t0, t0, -1 

    ble t0, zero, finished

    addi t1, t1, 4 # move one number to the right

    lw t3, (t1) # load the next number into t3

    bge t2, t3, loop

    mv t2, t3 # if not, save the new largest number on t2
	
	
    j loop


finished: 
sw t2, (s0)

.equ LEDs, 0xFF200000
la t4, LEDs
sw t2,(t4)

iloop: j iloop



.data

result: .word 0
n:	.word 15
numbers: .word 4,5,3,6
	.word 1, 8, 2, 7
	.word 12, 99, 120, 10
	.word 11, 13, 19
