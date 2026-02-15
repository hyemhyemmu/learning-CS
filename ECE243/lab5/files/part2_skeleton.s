.global _start
_start:


.equ HEX_BASE1, 0xff200020
.equ HEX_BASE2, 0xff200030

.equ PUSH_BUTTON, 0xFF200050

#Your code goes below here:

#Your code should:

#Turn off interrupts in case an interrupt is called before correct set up

#Initialize the stack pointer

#activate interrupts from IRQ18 (Pushbuttons)

#Set the mtvec register to be the interrupt_handler location

/*Allow interrupts on the pushbutton's interrupt mask register, and any 
#additional set up for the pushbuttons */

#Now that everything is set, turn on Interrupts in the mstatus register

IDLE: j IDLE #Infinite loop while waiting on interrupt

interrupt_handler:
	addi sp, sp, -12
	
	sw s0, 0(sp)
	sw s1, 4(sp)
	sw ra, 8(sp)
	
	li s0, 0x7FFFFFFF  
	csrr s1, mcause
	
	and s1, s1, s0
	li  s0,18
	bne s1, s0, end_interrupt
	
	jal KEY_ISR # If so call KEY_ISR
	
	end_interrupt:

	
	lw s0, 0(sp)
	lw s1, 4(sp)
	lw ra, 8(sp)
	
	addi sp, sp, 12
	

mret

KEY_ISR: 

#Your KEY_ISR code here

ret