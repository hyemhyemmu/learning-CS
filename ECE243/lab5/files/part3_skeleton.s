.global _start
_start:

	.equ LEDs,  0xFF200000
	.equ TIMER, 0xFF202000

	#Set up the stack pointer
	
	jal    CONFIG_TIMER        # configure the Timer
    jal    CONFIG_KEYS         # configure the KEYs port
	
	/*Enable Interrupts in the NIOS V processor, and set up the address handling
	location to be the interrupt_handler subroutine*/
	
	la s0, LEDs
	la s1, COUNT
	
	LOOP:
		lw     s2, 0(s1)          # Get current count
		sw     s2, 0(s0)          # Store count in LEDs
	j      LOOP




interrupt_handler:
	#Code not shown
mret

CONFIG_TIMER: 

	#Code not shown

ret

CONFIG_KEYS: 

	#Code not shown

ret

.data
/* Global variables */
.global  COUNT
COUNT:  .word    0x0            # used by timer

.global  RUN                    # used by pushbutton KEYs
RUN:    .word    0x1            # initial value to increment COUNT

.end
