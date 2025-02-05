.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:
# Prologue: 保存寄存器
    addi sp, sp, -36
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw s5, 20(sp)
    sw s6, 24(sp)
    sw s7, 28(sp)
    sw ra, 32(sp)

    # 保存参数到s寄存器
    mv s0, a0   # m0指针
    mv s1, a1   # m0行数
    mv s2, a2   # m0列数
    mv s3, a3   # m1指针
    mv s4, a4   # m1行数
    mv s5, a5   # m1列数
    mv s6, a6   # d指针

    # 错误检查
    li t0, 1
    blt s1, t0, error_dim    # m0行数 <1
    blt s2, t0, error_dim    # m0列数 <1
    blt s4, t0, error_dim    # m1行数 <1
    blt s5, t0, error_dim    # m1列数 <1
    bne s2, s4, error_dim    # m0列数 != m1行数

    # 初始化外层循环计数器
    li s7, 0
outer_loop:  // 乘以每一行
    bge s7, s1, outer_loop_end  // 大于m0行的时候结束循环
    
    li s8,0 # 内层循环计数器


inner_loop:  // 乘以每一列
    bge s8, s5, inner_loop_end

    # 行的地址
    mul t0, s7, s2 # 第几个元素
    slli t0, t0, 2 # 对应的偏移量
    add a0, s0, t0 # 起始地址加上偏移量就是这一行的地址

    # 列的地址
    mul t0, s8, s4
    slli t0, t0, 2
    add a1, s3, t0

    # 配置dot函数参数
    mv a2, s2
    li a3, 1 # m0步长为1
    li a4, s5 # m1步长为列数

    # 执行dot
    jal ra, dot
    
    # 后续操作 - a0 是i*j的结果 - 存储d
    # 放到的地址- d+(i*列数+j)*4
    mul t1, s7, s5
    add t1, t1, s8
    slli t1, 2
    sw a0, 0(t1) #存储结果

    #列数+1 继续循环
    addi s8, s8, 1
    j inner_loop

inner_loop_end: 
    addi s7, s7, 1
    j outer_loop

outer_loop_end:
    # Epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    lw s5, 20(sp)
    lw s6, 24(sp)
    lw s7, 28(sp)
    lw ra, 32(sp)
    addi sp, sp, 36
    jr ra

error:
    li a0, 38
    li a7, 93
    ecall