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
    sw a0,0(sp) //把原来a0里的数据存放起来，因为后面会被修改

    mv a1,a0
    jal mult //调用mult，结果存储在a0

    lw a0,0(sp) //恢复a0的数据
    add a0,a0,a1

    lw ra,4(sp) //大函数的地址
    addi sp,sp,8
    jr ra
