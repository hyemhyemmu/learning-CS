.global _start
_start:


.equ HEX_BASE1, 0xff200020
.equ HEX_BASE2, 0xff200030

.equ PUSH_BUTTON, 0xFF200050

#Your code goes below here:

#Your code should:

#Turn off interrupts in case an interrupt is called before correct set up
csrw mstatus, zero

#Initialize the stack pointer
la sp, 0x20000

#activate interrupts from IRQ18 (Pushbuttons)
# key side
la t0, PUSH_BUTTON #t0 - addr of keys
li t1, 0b1111 
sw t1, 8(t0) # enable interrupt for all the keys
sw t1, 0xC(t0) # clear edgecapture reg just in case 

# cpu side
li t0, 0x40000 # IRQ18
csrs mie, t0
li t1, 0b1000 

#Set the mtvec register to be the interrupt_handler location
la t0, interrupt_handler 
csrw mtvec, t0


/*Allow interrupts on the pushbutton's interrupt mask register, and any 
#additional set up for the pushbuttons */

#Now that everything is set, turn on Interrupts in the mstatus register
csrs mstatus, t1 # set bit 3 to 1 to enable software interrupt

IDLE: j IDLE #Infinite loop while waiting on interrupt

interrupt_handler:
	addi sp, sp, -40
	sw ra, 0(sp)
    sw t0, 4(sp)
    sw t1, 8(sp)
    sw t2, 12(sp)
    sw t3, 16(sp)
    sw t4, 20(sp)
    sw s0, 24(sp)
    sw s1, 28(sp)
    sw a0, 32(sp)
    sw a1, 36(sp)
	
	# verify
	li s0, 0x7FFFFFFF  
	csrr s1, mcause
	
	and s1, s1, s0
	li  s0,18
	bne s1, s0, end_interrupt
	
	jal KEY_ISR # If so call KEY_ISR
	
end_interrupt:
	lw ra, 0(sp)
    lw t0, 4(sp)
    lw t1, 8(sp)
    lw t2, 12(sp)
    lw t3, 16(sp)
    lw t4, 20(sp)
    lw s0, 24(sp)
    lw s1, 28(sp)
    lw a0, 32(sp)
    lw a1, 36(sp)
    
    addi sp, sp, 40
    mret
	
# --------------------- KEY ISR --------

KEY_ISR: 
	#Your KEY_ISR code here
	la t0, PUSH_BUTTON
	lw t1, 0xC(t0) # load edge capture reg - t1
	sw t1, 0xC(t0) # clear the bit right away
	bne t1, zero, KEY_PUSHED_ISR 

problem: j problem # somewhere wrong


KEY_PUSHED_ISR:
	addi sp, sp, -4
	sw ra, 0(sp) # save ra

	la t2, HEX_STATUS # t2 - hex status addr
	lw t3, 0(t2) # t3 - hex status - load current hex display status
	xor t3, t3, t1 # toggle the status, now t3 has new status
	sw t3, 0(t2) # store new hex status

CHECK_KEY0:
	andi t4, t1, 0b0001 # check key0
	beq t4, zero, CHECK_KEY1

	li a0, 0
	li a1, 0

	# check hex - the new one 
	andi t4, t3, 0b0001
	bne t4, zero, CALL_DISP # 1 - light the hex

	# 0 - blank the hex
	li a0, 0b10000
	j CALL_DISP


CHECK_KEY1:
	andi t4, t1, 0b0010 # check key1
	beq t4, zero, CHECK_KEY2

	li a0, 1
	li a1, 1

	# check hex - the new one 
	andi t4, t3, 0b0010
	bne t4, zero, CALL_DISP # 1 - light the hex

	# 0 - blank the hex
	li a0, 0b10000
	j CALL_DISP
	
CHECK_KEY2:
	andi t4, t1, 0b0100 # check key2
	beq t4, zero, CHECK_KEY3

	li a0, 2
	li a1, 2

	# check hex - the new one 
	andi t4, t3, 0b0100
	bne t4, zero, CALL_DISP # 1 - light the hex

	# 0 - blank the hex
	li a0, 0b10000
	j CALL_DISP

CHECK_KEY3:
	andi t4, t1, 0b1000 # check key3
	beq t4, zero, END_ISR

	li a0, 3
	li a1, 3

	# check hex - the new one 
	andi t4, t3, 0b1000
	bne t4, zero, CALL_DISP # 1 - light the hex

	# 0 - blank the hex
	li a0, 0b10000
	j CALL_DISP

	
CALL_DISP:
	jal HEX_DISP
	
END_ISR:
	lw ra, 0(sp)
	addi sp, sp, 4
	ret


# ---- placed in another file - hex.s
HEX_DISP:   
		addi sp, sp, -16           # store the 4 registers being used in this subroutine on the stack
		sw s0,0(sp)
		sw s1,0x4(sp)
		sw s2,0x8(sp)
		sw s3,0xC(sp)
	
		la   s0, BIT_CODES         # s0 - starting address of the bit codes
	    andi     s1, a0, 0x10	       # s1 - get bit 4 of the input
	    beq      s1, zero, not_blank 
	    mv      s2, zero # s2 - zero - the number to display
	    j       DO_DISP
		
not_blank:  andi     a0, a0, 0x0f	   # a0 - target number - lower 4 bit
            add      a0, a0, s0        # add the offset to the bit codes
            lb      s2, 0(a0)         # index into the bit codes

#Display it on the target HEX display
DO_DISP:    
			la       s0, HEX_BASE1         # s0 - load hex address
			li       s1,  4 # s1 - 4 - to calculate relative position in base2
			blt      a1,s1, FIRST_SET      # hex4 and hex 5 are on 0xff200030
			sub      a1, a1, s1            # a1 - pos - if hex4 or hex5, we need to adjust the shift
			addi     s0, s0, 0x0010        # we also need to adjust the address
FIRST_SET:
			slli     a1, a1, 3             # hex*8 shift is needed
			addi     s3, zero, 0xff        # create bit mask so other values are not corrupted
			sll      s3, s3, a1 
			li     	 a0, -1
			xor      s3, s3, a0  
    		sll      a0, s2, a1            # shift the hex code we want to write
			lw    	 a1, 0(s0)             # read current value       
			and      a1, a1, s3            # and it with the mask to clear the target hex
			or       a1, a1, a0	           # or with the hex code
			sw    	 a1, 0(s0)		       # store back
END:			
			mv 		 a0, s2				   # put bit pattern on return register
			
			
			lw s0,0(sp)			# restore those same 4 registers from the stack.
			lw s1,0x4(sp)
			lw s2,0x8(sp)
			lw s3,0xC(sp)
			addi sp, sp, 16
			ret


.data
BIT_CODES:  .byte     0b00111111, 0b00000110, 0b01011011, 0b01001111
			.byte     0b01100110, 0b01101101, 0b01111101, 0b00000111
			.byte     0b01111111, 0b01100111, 0b01110111, 0b01111100
			.byte     0b00111001, 0b01011110, 0b01111001, 0b01110001
			

HEX_STATUS: 
	.align 2
	.word 0

            .end
			
