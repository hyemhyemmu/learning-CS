.globl read_matrix

.text
# =============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
#   - If malloc returns an error,
#     this function terminates the program with error code 26
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fread error or eof,
#     this function terminates the program with error code 29
# =============================================================================
read_matrix:
    # Prologue
    addi sp, sp, -24 
    sw ra, 20(sp)
    sw s0, 16(sp)   # 存储文件描述符
    sw s1, 12(sp)   # 存储行
    sw s2, 8(sp)    # 存储列
    sw s4, 0(sp)    # 存储矩阵指针

    mv s1, a1       
    mv s2, a2

    # 1. 打开文件
    li a1, 0
    call fopen
    li t0, -1
    beq t0, a0, fopen_error
    mv s0, a0

    # 2. 读取文件
    # 分配内存
    addi sp, sp, -8
    mv a1, sp
    li a2, 8
    mv a0, s0
    call fread
    li t0, 8
    bne a0, t0, fread_error

    # 提取行列数
    lw t0, 0(sp)
    lw t1, 4(sp)
    addi sp, sp, 8
    
    # 存储行列数
    sw t0, 0(s1)
    sw t1 ,0(s2)

    # 3. 分配矩阵内存
    # 计算所需空间大小
    lw t0, 0(s1)    
    lw t1, 0(s2)    
    mul t2, t0, t1  
    slli a0, t2, 2  
    jal malloc      
    beqz a0, malloc_error
    mv s4, a0   

    # 读取矩阵
    mv a1, s4       
    lw t2, 0(s1)    
    lw t3, 0(s2)    
    mul t2, t2, t3  
    slli a2, t2, 2  
    mv a0, s0       
    jal fread       
    bne a0, a2, fread_error


    # 3. 关闭文件
    mv a0, s0
    call fclose
    li t0, -1
    beq a0, t0, fclose_error

    mv a0, s4

    # 正常退出
    j epilogue


# 错误处理
fopen_error:
    li a0, 27       # 错误码 27（文件打开失败）
    j exit

fread_error:
    li t0, 29       # 错误码 29（读取失败）
    j error_handler


malloc_error:
    li t0, 26       # 错误码 26（内存分配失败）
    j error_handler

fwrite_error:
    li t0, 30       # 错误码30（写入失败）
    j error_handler 

fclose_error:
    li a0, 28       # 错误码 28（文件关闭失败）
    j exit

error_handler:
    # 通用错误处理：尝试关闭文件并设置错误码
    mv a0, s0       # 文件描述符
    call fclose     # 尝试关闭文件
    li t1, -1
    beq a0, t1, error_handler_fclose_fail  # 关闭失败则覆盖错误码为 28
    mv a0, t0       # 使用原有错误码
    j exit
error_handler_fclose_fail:
    li a0, 28       # 错误码 28（文件关闭失败）
    j exit

# ------------------------------
# 尾声：恢复寄存器并返回
# ------------------------------
epilogue:
    lw ra, 20(sp)
    lw s0, 16(sp)
    lw s1, 12(sp)
    lw s2, 8(sp)
    lw s3, 4(sp)
    lw s4, 0(sp)
    addi sp, sp, 24
    jr ra

# ------------------------------
# 退出程序（系统调用）
# ------------------------------
exit:
    li a7, 93       # 系统调用号 93（exit）
    ecall
