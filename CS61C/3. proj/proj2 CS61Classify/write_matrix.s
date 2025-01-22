.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fwrite error or eof,
#     this function terminates the program with error code 30
# ==============================================================================
write_matrix:

    # Prologue
    addi sp, sp, -20
    sw ra, 0(sp)
    sw s0, 4(sp) # 存放指向内存中矩阵存放位置的指针
    sw s1, 8(sp) # 存放文件标识符
    sw s2, 12(sp) # 存放行数
    sw s3, 16(sp) # 存放列数


    mv s0, a1
    mv s2, a2
    mv s3, a3

    # 1. 读取文件
    li a1, 1
    call fopen
    li t0, -1
    beq a0, t0, fopen_error
    mv s1, a0
    
    # 把行数和列数也放入缓冲区
    addi sp, sp, -8
    sw s2, 0(sp)
    sw s3, 4(sp)

    # 2. 把行列数写入文档
    mv a0, s1
    lw a1, sp
    li a2, 2
    li a3, 4
    call fwrite

    beq a0, a2, fwrite_error

    # 3. 写入矩阵
    lw a0, s1
    lw a1, s0
    mul t0, s2, s3
    mv a2, t0
    li a3, 4
    call fwrite

    bne a0, a2, fwrite_error
    addi sp, sp, 8

    # 4. 关闭文件
    lw a0, s1
    call fclose 
    li t0, -1
    beq a0, t0, fclose_error

        # Epilogue
    lw ra, 0(sp)      # 恢复返回地址
    lw s0, 4(sp)      # 恢复寄存器 s0
    lw s1, 8(sp)      # 恢复寄存器 s1
    lw s2, 12(sp)     # 恢复寄存器 s2
    lw s3, 16(sp)     # 恢复寄存器 s3
    addi sp, sp, 20   # 恢复堆栈指针
    jr ra             # 返回到调用函数

# 错误处理标签
fopen_error:
    li a0, 27         # 设置错误代码 27
    call exit         # 退出程序

fwrite_error:
    li a0, 30         # 设置错误代码 30
    call exit         # 退出程序

fclose_error:
    li a0, 28         # 设置错误代码 28
    call exit         # 退出程序

    
    










    # Epilogue


    jr ra
