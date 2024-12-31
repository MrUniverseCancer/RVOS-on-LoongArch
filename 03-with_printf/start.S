

	# size of each hart's stack is 1024 bytes

	.data
	.align 4
STACK_SIZE:
	.word 1024
	.align 4


	.global	_start

	.text
_start:

	la.local $t0, stacks
	la.local $t1, STACK_SIZE
	ld.w     $t1, $t1, 0
	add.w   $sp, $t0, $t1
					# set the initial stack pointer
					# to the end of the first stack space
	
	# la.local $t0, start_kernel
	# jr $t0
	b start_kernel

stacks:
	.space 1024
	.align 4


	.end				# End of file
