/*int mult(int a, int b) {
    return a * b;
}

int sumSquarePlus(int x, int y) {
    // 计算 x^2 和 y^2，然后相加再加 1
    return mult(x, x) + mult(y, y) + 1;
}

int main() {
    int x = 3, y = 4;
    int result = sumSquarePlus(x, y);
    printf("The result of sumSquarePlus(%d, %d) is: %d\n", x, y, result);
    return 0;
}*/

mult:
    mul a0,a0,a1
    jr ra

sumSquarePlus:
    //使用堆栈保留x,y和ra
    addi sp,sp,-12 
    sw a0,0(sp)
    sw a1,4(sp)
    sw ra,8(sp)

    //计算mult(x,x)
    mv a1,a0
    jal mult
    mv t0,a0 //先把结果放在t0

    //计算mult(x,x)
    lw a0,4(sp)
    mv a1,a0
    jal mult
    mv t1,a0

    //计算加和
    add a0,t0,t1
    addi a0,a0,1

    //恢复堆栈中寄存器的值
    lw a0,0(sp)
    lw a1,4(sp)
    lw ra,8(sp)

    //恢复堆栈
    addi sp,sp,12
    jr ra
