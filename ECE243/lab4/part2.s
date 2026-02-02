.global _start
_start:
	.equ KEY_BASE, 0xFF200050
	.equ LED, 0xFF200000
	.equ EDGE_OFFSET, 0xc
	.equ COUNTER_DELAY, 500000 
	
	la s0, KEY_BASE # s0 - addr of keys
	la s1, LED # s1 - addr of leds
	li s2, 0 # s2 - counter
	li s3, 1 # s3 - status (1-run, 0-stop)
	li sp, 0x20000

	
MAIN:
	sw s2, (s1)
	call DELAY	
	lw t0, EDGE_OFFSET(s0) # t0 - value in Edgecapture register
	
	bne t0, zero, FLIP_STATUS
	
	# no key input - decide to add or not base on current status
	beqz s3, MAIN
	
	addi s2, s2, 1
	andi s2, s2, 0xFF # use mask to prevent s2>255
	j MAIN
	
	
	
DELAY:
    # save s0 to stack
    addi sp, sp, -4
    sw s0, (sp)

	li s0, COUNTER_DELAY 
SUB_LOOP: 
	addi s0, s0, -1      
	bnez s0, SUB_LOOP    

    # pop s0 out of stack
    lw s0, (sp)
    addi sp, sp, 4

    ret                 

FLIP_STATUS:
	xori s3, s3, 1 # flip current status
	sw t0, EDGE_OFFSET(s0) # reset Edgecapture register
	j MAIN