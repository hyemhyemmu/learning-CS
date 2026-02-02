.global _start
_start:
	.equ KEY_BASE, 0xFF200050
	.equ LED, 0xFF200000
	
	la s0, KEY_BASE # s0 - addr of keys
	la s1, LED # s1 - addr of leds
	li s2, 0x1 # s2 - value to be displayed on leds, 	
				# initialized to 1
	
MAIN:
	sw s2, (s1)
	
POLL_KEYS:
	lw t0, (s0) # load data regs of keys to t0
	beqz t0, POLL_KEYS # keep waiting until any of the bits is nonzero
	
	andi t1, t0, 0x1 # KEY0 result
	bne t1, zero, HANDLE_KEY0
	
	andi t1, t0, 0x2 # KEY1 result
	bne t1, zero, HANDLE_KEY1
	
	andi t1, t0, 0x4 # KEY2 result
	bne t1, zero, HANDLE_KEY2
	
	andi t1, t0, 0x8 # KEY3 result
	bne t1, zero, HANDLE_KEY3
	
	j POLL_KEYS
	
WAIT_RELEASE:
	lw t0, (s0) 
	bne t0, zero, WAIT_RELEASE # keep waiting all bits are zero
	j POLL_KEYS # back to polling

UPDATE_LED:
	sw s2, (s1) # update leds
	j WAIT_RELEASE
	
# -------------
HANDLE_KEY0:
	beqz s2, RESET
	li s2, 0x1 # display 1
	j UPDATE_LED

HANDLE_KEY1:
	beqz s2, RESET
	li t2, 15 # upper bound
	beq s2, t2, UPDATE_LED # no more adding if at boundary
	addi s2, s2, 1
	j UPDATE_LED
	
HANDLE_KEY2:
	beqz s2, RESET
	li t2, 1 # lower bound
	beq s2, t2, UPDATE_LED # no more decreasing if at boundary
	addi s2, s2, -1
	j UPDATE_LED
	
HANDLE_KEY3:
	li s2, 0
    j UPDATE_LED
	
	
RESET:
	# press key012 to reset led to 1
	li s2, 0x1
	j UPDATE_LED

	
	