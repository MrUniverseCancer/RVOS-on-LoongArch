csrwr == csrrw
beqz == beq xx r0(默认r0为0)
mscratch == SAVE0-3
![alt text](8182b6b9d68d4ef7658d4d819aba3bf.png)
SAVE0=0x30

entry.S:79: Fatal error: no match insn: csrwr   a7,0x30
csr指令报错，因为没有对应的csr指令，需要自己实现