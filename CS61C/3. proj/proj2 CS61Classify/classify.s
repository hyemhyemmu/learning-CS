.globl classify

.text
# =====================================
# COMMAND LINE ARGUMENTS
# =====================================
# Args:
#   a0 (int)        argc
#   a1 (char**)     argv
#   a1[1] (char*)   pointer to the filepath string of m0
#   a1[2] (char*)   pointer to the filepath string of m1
#   a1[3] (char*)   pointer to the filepath string of input matrix
#   a1[4] (char*)   pointer to the filepath string of output file
#   a2 (int)        silent mode, if this is 1, you should not print
#                   anything. Otherwise, you should print the
#                   classification and a newline.
# Returns:
#   a0 (int)        Classification
# Exceptions:
#   - If there are an incorrect number of command line args,
#     this function terminates the program with exit code 31
#   - If malloc fails, this function terminates the program with exit code 26
#
# Usage:
#   main.s <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>
classify:
    # Prologue
    addi sp, sp, -64
    sw ra, 60(sp)
    sw s0, 56(sp)   # argv
    sw s1, 52(sp)   # silent mode flag
    sw s2, 48(sp)   # m0_ptr
    sw s3, 44(sp)   # m1_ptr
    sw s4, 40(sp)   # input_ptr
    sw s5, 36(sp)   # h_ptr
    sw s6, 32(sp)   # o_ptr
    sw s7, 28(sp)   # m0_rows
    sw s8, 24(sp)   # m0_cols
    sw s9, 20(sp)   # m1_rows
    sw s10, 16(sp)  # m1_cols
    sw s11, 12(sp)  # o_size

    # Check argc == 5
    li t0, 5
    bne a0, t0, argc_error
    mv s0, a1       # Save argv
    mv s1, a2       # Save silent mode flag

    # Read pretrained m0
    # Allocate space for row/col pointers (6 integers)
    li a0, 24       # 6*4=24 bytes
    call malloc
    beqz a0, malloc_error
    mv t1, a0       # t1 = dimension buffer

    # Load m0
    lw a0, 4(s0)    # argv[1] = m0 path
    mv a1, t1       # rows ptr
    addi a2, t1, 4  # cols ptr
    call read_matrix
    beqz a0, read_error
    mv s2, a0       # s2 = m0_ptr
    lw s7, 0(t1)    # s7 = m0_rows
    lw s8, 4(t1)    # s8 = m0_cols

    # Read input matrix
    lw a0, 12(s0)   # argv[3] = input path
    addi a1, t1, 8  # input rows ptr
    addi a2, t1, 12 # input cols ptr
    call read_matrix
    beqz a0, read_error
    mv s4, a0       # s4 = input_ptr
    lw t2, 8(t1)    # input_rows
    lw t3, 12(t1)   # input_cols

    # Check m0_cols == input_rows
    bne s8, t2, matmul_error

    # Compute h = matmul(m0, input)
    mul t4, s7, t3  # h_size = m0_rows * input_cols
    slli a0, t4, 2  # bytes needed
    call malloc
    beqz a0, malloc_error
    mv s5, a0       # s5 = h_ptr

    mv a0, s2       # m0_ptr
    mv a1, s7       # m0_rows
    mv a2, s8       # m0_cols
    mv a3, s4       # input_ptr
    mv a4, t2       # input_rows
    mv a5, t3       # input_cols
    mv a6, s5       # h_ptr
    call matmul

    # Compute h = relu(h)
    mv a0, s5       # h_ptr
    mv a1, t4       # h_size
    call relu

    # Read pretrained m1
    lw a0, 8(s0)    # argv[2] = m1 path
    addi a1, t1, 16 # m1_rows ptr
    addi a2, t1, 20 # m1_cols ptr
    call read_matrix
    beqz a0, read_error
    mv s3, a0       # s3 = m1_ptr
    lw s9, 16(t1)   # m1_rows
    lw s10, 20(t1)  # m1_cols

    # Check m1_cols == h_rows (m0_rows)
    bne s10, s7, matmul_error

    # Compute o = matmul(m1, h)
    mul s11, s9, t3 # o_size = m1_rows * input_cols
    slli a0, s11, 2 # bytes needed
    call malloc
    beqz a0, malloc_error
    mv s6, a0       # s6 = o_ptr

    mv a0, s3       # m1_ptr
    mv a1, s9       # m1_rows
    mv a2, s10      # m1_cols
    mv a3, s5       # h_ptr
    mv a4, s7       # h_rows (m0_rows)
    mv a5, t3       # h_cols (input_cols)
    mv a6, s6       # o_ptr
    call matmul

    # Write output matrix o
    lw a0, 16(s0)   # argv[4] = output path
    mv a1, s6       # o_ptr
    mv a2, s9       # o_rows (m1_rows)
    mv a3, t3       # o_cols (input_cols)
    call write_matrix

    # Compute and return argmax(o)
    mv a0, s6       # o_ptr
    mv a1, s11      # o_size
    call argmax
    mv t0, a0       # Save result

    # If enabled, print argmax(o) and newline
    bnez s1, skip_print
    mv a0, t0
    call print_int
    li a0, '\n'
    call print_char
skip_print:

    # Free all allocated memory
    mv a0, s2
    call free
    mv a0, s3
    call free
    mv a0, s4
    call free
    mv a0, s5
    call free
    mv a0, s6
    call free
    mv a0, t1
    call free

    # Epilogue
    mv a0, t0       # Return value
    lw ra, 60(sp)
    lw s0, 56(sp)
    lw s1, 52(sp)
    lw s2, 48(sp)
    lw s3, 44(sp)
    lw s4, 40(sp)
    lw s5, 36(sp)
    lw s6, 32(sp)
    lw s7, 28(sp)
    lw s8, 24(sp)
    lw s9, 20(sp)
    lw s10, 16(sp)
    lw s11, 12(sp)
    addi sp, sp, 64
    jr ra

# ========== Error Handlers ==========
argc_error:
    li a0, 31
    j exit

malloc_error:
    li a0, 26
    j cleanup

read_error:
    li a0, 29
    j cleanup

matmul_error:
    li a0, 30       # Custom error code for dimension mismatch
    j cleanup

cleanup:
    # Free partially allocated resources
    beqz t1, cleanup_end
    mv a0, t1
    call free
cleanup_end:
    beqz s2, no_m0
    mv a0, s2
    call free
no_m0:
    beqz s3, no_m1
    mv a0, s3
    call free
no_m1:
    beqz s4, no_input
    mv a0, s4
    call free
no_input:
    beqz s5, no_h
    mv a0, s5
    call free
no_h:
    beqz s6, no_o
    mv a0, s6
    call free
no_o:
    j exit

exit:
    li a7, 93
    ecall