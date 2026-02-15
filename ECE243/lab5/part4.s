.global _start
_start:

	.equ LEDs,  0xFF200000
	.equ TIMER, 0xFF202000
	.equ KEYS, 0xFF200050
	.equ IRQ_KEYS, 18
	.equ IRQ_TIMER, 16

	#Set up the stack pointer
	li sp, 0x20000
	
	csrw mstatus, zero
	csrw mie, zero
	
	jal    CONFIG_TIMER        # configure the Timer
    jal    CONFIG_KEYS         # configure the KEYs port
	
	/*Enable Interrupts in the NIOS V processor, and set up the address handling
	location to be the interrupt_handler subroutine*/
	# handler location
	la t1, interrupt_handler
	csrw mtvec, t1
	
	li t1, 0b1000 
	csrs mstatus, t1 # enable interrupt
	
	la s0, LEDs
	la s1, COUNT
	
	
	LOOP:
		lw     s2, 0(s1)          # Get current count
		sw     s2, 0(s0)          # Store count in LEDs
		j      LOOP




interrupt_handler:
	addi sp, sp, -32
	sw t1, 0(sp)
	sw t2, 4(sp)
	sw t3, 8(sp)
	sw s0, 12(sp)
	sw s1, 16(sp)
	sw s2, 20(sp)
	sw t0, 24(sp)
	sw t4, 28(sp)
	
	# check who cause interrupt
	li t0, 0x7FFFFFFF
	csrr t1, mcause
	and t2, t1, t0 # t2 gets the IRQ	
	
	# if is timer
	li t0, IRQ_TIMER
	beq t2, t0, TIMER_ISR
	
	
	# if is keys
	li t0, IRQ_KEYS
	beq t2, t0, KEY_ISR
	
	j ISR_DONE
	
TIMER_ISR:
    la t0, COUNT 
    la t1, RUN
    
    lw t2, 0(t0) # t2 - count
    lw t3, 0(t1) # t3 - run
    
    add t2, t2, t3 # t2 = COUNT + RUN
    
    li t4, 255
    ble t2, t4, SAVE_RESULT # compare
    
    li t2, 0 # reset to 0 

SAVE_RESULT:
    sw t2, 0(t0) # save COUNT
    la t0, TIMER
    sw zero, 0(t0) # reset interrupt

    j ISR_DONE 


KEY_ISR:
    la t0, TIMER
	# stop1 start0 cont1 ito1
    li t1, 0b1011         
    sw t1, 4(t0) # stop the timer first 

    # check which key is pressed
    la t0, KEYS
    lw t1, 12(t0)  # t1 - edgecapture reg

CHECK_KEY0:
    andi t2, t1, 0x1   
    beq t2, zero, CHECK_KEY1     
  
  	# key0 - toggle run
    la t3, RUN
    lw t4, 0(t3)
    xori t4, t4, 1
    sw t4, 0(t3)
    
    j RESTART_TIMER      

CHECK_KEY1:
    andi t2, t1, 0x2         # Check Bit 1
    beq t2, zero, CHECK_KEY2

    la t3, CURRENT_PERIOD  
    lw t4, 0(t3)       
    srli t4, t4, 1 # period/2 -> speed x2
    beq t4, zero, RESTART_TIMER # peirod cant be zero
    
    sw t4, 0(t3) # save new period
    j UPDATE_TIMER_HW  

CHECK_KEY2:
    andi t2, t1, 0x4  
    beq t2, zero, CLEAR_key_ISR 

    la t3, CURRENT_PERIOD
    lw t4, 0(t3)
	slli t4, t4, 1 # period*2 -> speed /2
	li t1, 20000 # maximum priod count
    blt t1, t5, RESTART_TIMER
 
    
    sw t4, 0(t3)           
	
UPDATE_TIMER_HW:
    la t0, TIMER
    la t3, CURRENT_PERIOD
    lw t4, 0(t3)  
    
	# store into timer reg in 2 parts
    li t1, 0xFFFF
    and t2, t4, t1  # t2 = Low 16 bits
    srli t3, t4, 16  # t3 = High 16 bits
    
    sw t2, 8(t0)   
    sw t3, 12(t0) 

RESTART_TIMER:
    la      t0, TIMER
    li      t1, 0b0111
    sw      t1, 4(t0)

CLEAR_key_ISR:
    la      t0, KEYS
    li      t1, 0xF 
    sw      t1, 12(t0)

    j ISR_DONE    


ISR_DONE:	
	lw t1, 0(sp)
	lw t2, 4(sp)
	lw t3, 8(sp)
	lw s0, 12(sp)
	lw s1, 16(sp)
	lw s2, 20(sp)
	lw t0, 24(sp)
	lw t4, 28(sp)
	addi sp, sp, 32
	
	mret


# ---------------------
CONFIG_TIMER: 
	la t0, TIMER # t0 - timer addr
	li t1, 0
	sw t1, 0(t0) # clear status reg
	
	li t1, 12500000 # 50M * 0.25s
	li t4, 0xFFFF
	and t2, t1, t4 # t2 - low 16 bits
	srli t3, t1, 16 # t3 - high 16 bits
	sw t2, 0x8(t0)
	sw t3, 0xC(t0)
	
	# configure control reg
	# stop0 start1 cont1 ito1
	li t1, 0b0111
	sw t1, 4(t0)
	
	li t1, (1<<IRQ_TIMER) # IRQ16
	csrs mie, t1 # enable timer interrupt in cpu
	
	ret

CONFIG_KEYS: 
	la t0, KEYS
	li t1, 0xF
	sw t1, 8(t0) # enable interrupt for all keys
	sw t1, 12(t0) # clear edgecapture reg
	
	li t1, (1<<IRQ_KEYS) # IRQ18
	csrs mie, t1 # enable timer interrupt in cpu
	
	ret

.data
/* Global variables */
.global  COUNT
COUNT:  .word    0x0            # used by timer

.global  RUN                    # used by pushbutton KEYs
RUN:    .word    0x1            # initial value to increment COUNT

.global CURRENT_PERIOD
CURRENT_PERIOD: .word 12500000

.end
