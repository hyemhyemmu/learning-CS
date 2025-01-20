.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the number of elements to use is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
    # Prologue
    addi sp, sp, -16
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    # prologue end

    # exceptions
    li t0, 1
    blt a2, t0, error1
    blt a3, t0, error2
    blt a4, t0, error2 

    # Initialize sum and current pointers
    li t0, 0          # sum = 0
    mv t1, a0         # current pointer for arr0
    mv t2, a1         # current pointer for arr1

loop:
    beq a2, zero, loop_end

    # load elements from both arrays
    lw t3, 0(t1)
    lw t4, 0(t2)

    # multipy and save
    mul t5, t3, t4
    add t0, t0, t5

    # move pointers
    slli t6, a3, 2 # offset per stride
    add t1, t1, t6
    slli t6, a4, 2
    add t2, t2, t6

    # decrement counter
    addi a2, a2, -1
    j loop

loop_end:
    # Epilogue
    mv a0, t0
    addi sp, sp, 20
    jr ra


error1:
    li a0, 36 //return error code 36
    li a7, 93
    ecall

error2:
    li a0, 37
    li a7, 93
    ecall