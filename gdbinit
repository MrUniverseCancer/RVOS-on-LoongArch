set disassemble-next-line on
set architecture Loongarch32
b start_kernel
target remote : 1234
c
