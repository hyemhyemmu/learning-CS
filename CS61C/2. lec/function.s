//function calls example

//example 1:
// f=(g+h)-(i+j)
# initialize space
addi sp,sp,-8 # malloc space for 2 int
sw s1,4(sp) 
sw s0,0(sp)

# main function
add s0, a0, a1; # s0 = a0 + a1, f=g+h 
add s1, a2, a3; # s1 = a2 + a3, s1=i+j
sub s0, s0, s1 # s0 = s0 - s1, return f 

# restore space
lw s0, 0(sp)
addi sp,sp,8
jr ra

