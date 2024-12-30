#include "platform.h"

	# size of each hart's stack is 1024 bytes

	.data
STACK_SIZE:
	.word 1024
stacks:
	.space 1024

	.global	_start

	.text
_start:

	la.local $t0, stacks
	la.local $t1, STACK_SIZE
	ld.w     $t1, $t1, 0
	add.w   $sp, $t0, $t1
					# set the initial stack pointer
					# to the end of the first stack space

	la.local $t0, start_kernel
	jr $t0


	.end				# End of file
