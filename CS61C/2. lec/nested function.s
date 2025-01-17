// tricky about nested functions: save address of the callers
# int sumSquare(int x, int y) {
#   return mult(x, x) + y;
# }
mult:
    mul a0,a0,a1
    jr ra

sumSquare:
    addi sp,sp,-8 //分配内存
    sw ra,4(sp)  //存放下一条指令的地址，防止被覆盖
    sw a0,0(sp)

    mv a1,a0
    jal mult //调用mult，结果存储在a0

    lw a0,0(sp)
