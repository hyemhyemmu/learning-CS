.global _start
_start:

# s3 should contain the grade of the person with the student number, -1 if not found
# s0 has the student number being searched

    li s0, 718293
	
	# s1 stores the address of Snumbers
	la s1, Snumbers
	
	# s2 stores the address of Grades (kind of like double pointer)
	la s2, Grades


# Your code goes below this line and above iloop
loop:
	lw t1, (s1) # move the Snumber s1 pointing to to t1
	beq t1, zero, fail # if last -> didn't find -> fail
	beq t1, s0, found # equal -> found
	# move pointers forward
	addi s1, s1, 4
	addi s2, s2, 1
	j loop
	
found:
	lb t2, (s2)
	j finish
	
fail:
	li t2, -1
	
finish:
	la t3, result        
    sb t2, 0(t3)
	.equ LEDs, 0xFF200000
    li t4, LEDs
    sw t2, 0(t4)
	

iloop: j iloop

/* result should hold the grade of the student number put into s0, or
-1 if the student number isn't found */ 

result: .byte 0
.align 4
		
/* Snumbers is the "array," terminated by a zero of the student numbers  */
Snumbers: .word 10392584, 423195, 644370, 496059, 296800
        .word 265133, 68943, 718293, 315950, 785519
        .word 982966, 345018, 220809, 369328, 935042
        .word 467872, 887795, 681936, 0

/* Grades is the corresponding "array" with the grades, in the same order*/
Grades: .byte 99, 68, 90, 85, 91, 67, 80
        .byte 66, 95, 91, 91, 99, 76, 68  
        .byte 69, 93, 90, 72