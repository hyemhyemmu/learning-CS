.data
n: .word 2
exp: .word 10

.text
main:
    # load the value of n into a0
    la a0 n
    lw a0 0(a0)

    # load the value of exp into a1
    la a1 exp
    lw a1 0(a1)

    # call ex3
    jal ra ex3

    # prints the output of ex3
    mv a1 a0
    li a0 1
    ecall # Print Result

    # exits the program
    li a0 17
    li a1 0
    ecall

# this is a recursive pow function
# a0 contains the base
# a1 contains the power to raise to
# the return value should be the result of a0^a1
#     where ^ is the exponent operator, not XOR
ex3:
    # Note: Add code BELOW without altering existing lines.
    addi sp, sp, -8  
    sw ra, 4(sp)     
    sw s0, 0(sp)     
    
    beq a1 x0 ex3_zero_case

    mv s0 a0         
    addi a1 a1 -1
    jal ra ex3
    mul a0 a0 s0    
    
    lw s0, 0(sp)     
    lw ra, 4(sp)
    addi sp, sp, 8
    j ex3_end

    # Note: Add code ABOVE without altering existing lines.

ex3_zero_case:
    li a0 1
    lw s0, 0(sp)    
    lw ra, 4(sp)
    addi sp, sp, 8

ex3_end:
    jr ra
