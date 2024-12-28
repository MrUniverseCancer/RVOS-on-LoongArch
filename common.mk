# Common part for the Makefile.
# This file will be included by the Makefile of each project.

# Custom Macro Definition (Common part)

include ../defines.mk
DEFS +=

CROSS_COMPILE = ../../loongson-gnu-toolchain-8.3-x86_64-loongarch32r-linux-gnusf-v2.0/bin/loongarch32r-linux-gnusf-
CFLAGS += -nostdlib -O2 -g3 -Wall -march=loongarch32 -mabi=ilp32 -ffreestanding -fno-common -I. -fno-stack-protector -fno-pie -no-pie

QEMU = ../../la32r-QEMU-x86_64-ubuntu-22.04/qemu-system-loongarch32
QFLAGS = -nographic -smp 1 -machine virt -m 4G -vga none -cpu la464

GDB = ${CROSS_COMPILE}gdb
CC = ${CROSS_COMPILE}gcc
LD = ${CROSS_COMPILE}ld
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump
MKDIR = mkdir -p
RM = rm -rf

OUTPUT_PATH = out

# SRCS_ASM & SRCS_C are defined in the Makefile of each project.
OBJS_ASM := $(addprefix ${OUTPUT_PATH}/, $(patsubst %.S, %.o, ${SRCS_ASM}))
OBJS_C   := $(addprefix $(OUTPUT_PATH)/, $(patsubst %.c, %.o, ${SRCS_C}))
OBJS = ${OBJS_ASM} ${OBJS_C}

ELF = ${OUTPUT_PATH}/os
BIN = ${OUTPUT_PATH}/os.bin


.DEFAULT_GOAL := all
all: ${OUTPUT_PATH} ${ELF}

${OUTPUT_PATH}:
	@${MKDIR} $@

# start.o must be the first in dependency!
#
# For USE_LINKER_SCRIPT == true, before do link, run preprocessor manually for
# linker script.
# -E specifies GCC to only run preprocessor
# -P prevents preprocessor from generating linemarkers (#line directives)
# -x c tells GCC to treat your linker script as C source file
${ELF}: ${OBJS}
# ifeq (${USE_LINKER_SCRIPT}, true)
# 	${CC} -E -P -x c ${DEFS} ${CFLAGS} os.ld > ${OUTPUT_PATH}/os.ld.generated
# endif
# ${CC} ${CFLAGS} 	
	${LD} ${LDFLAGS} -o ${ELF} $^
	${OBJCOPY} -O binary ${ELF} ${BIN}

${OUTPUT_PATH}/%.o : %.c
	${CC} ${DEFS} ${CFLAGS} -c -o $@ $<

${OUTPUT_PATH}/%.o : %.S
	${CC} ${DEFS} ${CFLAGS} -c -o $@ $<

run: all
	@${QEMU} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	@${QEMU} ${QFLAGS} -kernel ${ELF}

.PHONY : debug
debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------------------------------"
	@${QEMU} ${QFLAGS} -kernel ${ELF} -s -S &
	@${GDB} ${ELF} -q -x ../gdbinit

.PHONY : code
code: all
	@${OBJDUMP} -S ${ELF} | less

.PHONY : clean
clean:
	@${RM} ${OUTPUT_PATH}
