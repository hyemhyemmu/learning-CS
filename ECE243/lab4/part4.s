.global _start
_start:
	.equ KEY_BASE, 0xFF200050
	.equ LED, 0xFF200000
	.equ EDGE_OFFSET, 0xc
	.equ COUNTER_DELAY, 1000000 # 0.01s 
	.equ TIMER_BASE, 0xFF202000
	
	# offset for timer
	.equ STATUS_OFF, 0
    .equ CONTROL_OFF, 4
    .equ LOW_OFF, 8
    .equ HIGH_OFF, 12
	
	la s0, KEY_BASE # s0 - addr of keys
	la s1, LED # s1 - addr of leds

	li s3, 1 # s3 - status (1-run, 0-stop)
	li s4, 0 # s4 - seconds
	li s5, 0 # s5 - hundredths of a second
	li sp, 0x20000
	
	li t0, TIMER_BASE
	li t1, COUNTER_DELAY # lower bits
	sw t1, LOW_OFF(t0)
	
	srli t1, t1, 16 # higher bits
	sw t1, HIGH_OFF(t0)

	# control - start1, cont1, ito0 - 0b110
	li t1, 0b110
	sw t1, CONTROL_OFF(t0)

	
MAIN:
	slli t3, s4, 7
	or t3, t3, s5 # t3 - concated time to be display
	sw t3, (s1)
		
	call DELAY	
	lw t0, EDGE_OFFSET(s0) # t0 - value in Edgecapture register
	
	bne t0, zero, FLIP_STATUS
	
	# no key input - decide to add or not base on current status
	beqz s3, MAIN
	
	# calculate value to display
	addi s5, s5, 1 # hundredth add 1
	li t2, 100
	bne s5, t2, MAIN # keep going loop if not full
	# hundredth full
	li s5, 0 # reset to 0
	addi s4, s4, 1
	li t2, 8
	bne s4, t2, MAIN # keep going loop if not full
	li s4, 0
	j MAIN
	
	
DELAY:
	li  t0, TIMER_BASE

POLL_TIMER:
	lw t1, STATUS_OFF(t0) # read status
	andi t1, t1, 1
	beqz t1, POLL_TIMER 
	
	# finish counting
	sw zero, STATUS_OFF(t0) # reset
	
    ret                 

FLIP_STATUS:
	xori s3, s3, 1 # flip current status
	sw t0, EDGE_OFFSET(s0) # reset Edgecapture register
	j MAIN