.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
    # Prologue start
    addi sp, sp, -12 //a0, a1, t0
    sw a0, 0(sp) // array pointer
    sw a1, 4(sp) // length
    sw t0, 8(sp) // counter
    # Prologue end
    
    li t1, 1
    blt a1, t1, error # if a1 < t then error

    li t0, 0 // initialize counter
    li t2, 0 // comparison basis
    j loop
    


loop:
    bge t0, a1, loop_end 

    slli t3, t0, 2 // t3=t0*4 (convert index to byte offset)
    add t3, t3 ,a0 // address of array[t0]
    lw t4, 0(t3)  // load element to t4 

    blt t4, t2, flip
    sw t4, 0(t3)
    addi t0, t0, 1
    j loop

loop_end:
    # Epilogue
    lw a0, 0(sp) // array pointer
    lw a1, 4(sp) // length
    lw t0, 8(sp) // counter
    addi sp, sp, 12 //a0, a1, t0

    jr ra


error:
    li a0, 36 //return error code 36
    li a7, 93
    ecall

flip:
    li t4, 0 
    