.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    # Prologue
    addi sp, sp, -8 
    sw a0, 0(sp) // pointer
    sw a1, 4(sp) // length

    li t0, 1 // comparison basis
    blt a1, t0, error 

    li t0, 0 // counter 
    lw t1, 0(a0) // initial value
    li t4, 0 // index

loop:
    bge t0, a1, loop_end

    slli t2, t0, 2 // convert to bytes
    add t2, t2, a0 // addr
    lw t3, 0(t2) // load element

    ble t3, t1, skip
    mv t1, t3
    mv t4, t0  // index of t3 becomes new t4

skip:
    add t0, t0, 1
    j loop 


loop_end:
    # Epilogue
    lw a0, 0(sp)     
    lw a1, 4(sp)    
    addi sp, sp, 8 
    mv a0, t4
    jr ra


error:
    li a0, 36 //return error code 36
    li a7, 93
    ecall