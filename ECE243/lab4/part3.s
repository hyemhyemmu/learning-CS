.global _start
_start:
	.equ KEY_BASE, 0xFF200050
	.equ LED, 0xFF200000
	.equ EDGE_OFFSET, 0xc
	.equ COUNTER_DELAY, 25000000 
	.equ TIMER_BASE, 0xFF202000
	
	# offset for timer
	.equ STATUS_OFF, 0
    .equ CONTROL_OFF, 4
    .equ LOW_OFF, 8
    .equ HIGH_OFF, 12
	
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

	li s0, TIMER_BASE
	li t1, COUNTER_DELAY # lower bits
	sw t1, LOW_OFF(s0)
	
	srli t1, t1, 16 # higher bits
	sw t1, HIGH_OFF(s0)
	
	# control - start1, cont0, ito0 - 0b100
	li t1, 0b100
	sw t1, CONTROL_OFF(s0)
	
SUB_LOOP:
	lw t1, STATUS_OFF(s0) # read status
	andi t1, t1, 1
	beqz t1, SUB_LOOP 
	
	# finish counting
	sw zero, STATUS_OFF(s0) # reset
	
	# pop s0 out of stack
    lw s0, (sp)
    addi sp, sp, 4

    ret                 

FLIP_STATUS:
	xori s3, s3, 1 # flip current status
	sw t0, EDGE_OFFSET(s0) # reset Edgecapture register
	j MAIN