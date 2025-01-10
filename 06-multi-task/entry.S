#define LOAD		ld.w
#define STORE		st.w
#define SIZE_REG	4

# Save all General-Purpose(GP) registers to context.

.macro reg_save base
    STORE $ra,  \base,  0x0000
    STORE $tp,  \base,  0x0004
    STORE $sp,  \base,  0x0008
    STORE $a0,  \base,  0x000C
    STORE $a1,  \base,  0x0010
    STORE $a2,  \base,  0x0014
    STORE $a3,  \base,  0x0018
    STORE $a4,  \base,  0x001C
    STORE $a5,  \base,  0x0020
    STORE $a6,  \base,  0x0024
    STORE $a7,  \base,  0x0028
    STORE $t0,  \base,  0x002C
    STORE $t1,  \base,  0x0030
    STORE $t2,  \base,  0x0034
    STORE $t3,  \base,  0x0038
    STORE $t4,  \base,  0x003C
    STORE $t5,  \base,  0x0040
    STORE $t6,  \base,  0x0044
    STORE $t7,  \base,  0x0048
    STORE $t8,  \base,  0x004C
    STORE $r21, \base,  0x0050
    STORE $fp,  \base,  0x0054
    STORE $s0,  \base,  0x0058
    STORE $s1,  \base,  0x005C
    STORE $s2,  \base,  0x0060
    STORE $s3,  \base,  0x0064
    STORE $s4,  \base,  0x0068
    STORE $s5,  \base,  0x006C
    STORE $s6,  \base,  0x0070
    STORE $s7,  \base,  0x0074
    STORE $s8,  \base,  0x0078
	# We don't save a26 here because it's used as the base.
.endm

# Restore all General-Purpose(GP) registers from the context
.macro reg_restore base
    LOAD $ra,  \base,  0x0000
    LOAD $tp,  \base,  0x0004
    LOAD $sp,  \base,  0x0008
    LOAD $a0,  \base,  0x000C
    LOAD $a1,  \base,  0x0010
    LOAD $a2,  \base,  0x0014
    LOAD $a3,  \base,  0x0018
    LOAD $a4,  \base,  0x001C
    LOAD $a5,  \base,  0x0020
    LOAD $a6,  \base,  0x0024
    LOAD $a7,  \base,  0x0028
    LOAD $t0,  \base,  0x002C
    LOAD $t1,  \base,  0x0030
    LOAD $t2,  \base,  0x0034
    LOAD $t3,  \base,  0x0038
    LOAD $t4,  \base,  0x003C
    LOAD $t5,  \base,  0x0040
    LOAD $t6,  \base,  0x0044
    LOAD $t7,  \base,  0x0048
    LOAD $t8,  \base,  0x004C
    LOAD $r21, \base,  0x0050
    LOAD $fp,  \base,  0x0054
    LOAD $s0,  \base,  0x0058
    LOAD $s1,  \base,  0x005C
    LOAD $s2,  \base,  0x0060
    LOAD $s3,  \base,  0x0064
    LOAD $s4,  \base,  0x0068
    LOAD $s5,  \base,  0x006C
    LOAD $s6,  \base,  0x0070
    LOAD $s7,  \base,  0x0074
    LOAD $s8,  \base,  0x0078
.endm

.text

# void switch_to(struct context *next);
.globl switch_to
.balign 4
# SAVE0 = 0x30
switch_to:

	csrwr	$a7, 0x30	# swap $a7 and mscratch
	beq 	$a7, $r0, next		# handle special
    reg_save $a7
    addi.w  $a6, $a7, 0   # mv $a7->a6
    csrwr	$a7, 0x30
    STORE   $a7, $a6, 30*SIZE_REG

next:
    csrwr  $t0, 0x30
    addi.w $a7, $t0, 0

	LOAD     $sp,$a7, 2*SIZE_REG
	LOAD     $ra,$a7, 0*SIZE_REG

    reg_restore $a7

    #ret
	jirl $r0, $ra, 0

.end
