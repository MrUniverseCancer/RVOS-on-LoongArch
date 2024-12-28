# 配置龙芯交叉编译工具链

> 基于x86_64的Linux系统，配置龙芯交叉编译工具链。

## 64位
### 1. 下载交叉编译工具链

[工具链下载](https://www.loongnix.cn/zh/toolchain/GNU/)，选择二进制版本下载

解压缩到指定目录

```shell
tar -xvf loongson-gnu-toolchain-8.3-x86_64-loongarch64-linux-gnu-rc1.6.tar
```

### 2. 测试是否可以使用

写一个简单的C程序，使用gcc, readelf等工具编译和查看

## 32位
### 1. 下载交叉编译工具链

[工具链下载](https://gitee.com/loongson-edu/la32r-toolchains/releases/tag/v0.0.3)，选择loongson-gnu-toolchain-8.3-x86_64-loongarch32r-linux-gnusf-v2.0.tar.xz下载

解压缩到指定目录同上

### 2. 测试是否可以使用

loongson-gnu-toolchain-8.3-x86_64-loongarch32r-linux-gnusf-v2.0解压后与test在同一目录下

在test目录下写一个简单的C程序

```c
#include<stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

使用交叉编译工具链编译

```shell
~/Downloads/test$ ../loongson-gnu-toolchain-8.3-x86_64-loongarch32r-linux-gnusf-v2.0/bin/loongarch32r-linux-gnusf-gcc -S ./hello.c
```

查看生成的汇编代码

```
	.file	"hello.c"
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Hello, World!\000"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi.w	$r3,$r3,-16
	st.w	$r1,$r3,12
	st.w	$r22,$r3,8
	addi.w	$r22,$r3,16
	la.local	$r4,.LC0
	bl	%plt(puts)
	or	$r12,$r0,$r0
	or	$r4,$r12,$r0
	ld.w	$r1,$r3,12
	ld.w	$r22,$r3,8
	addi.w	$r3,$r3,16
	jr	$r1
	.size	main, .-main
	.ident	"GCC: (LoongArch GNU toolchain LA32 v2.0 (20230903)) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
```

使用readelf查看生成的可执行文件

```shell
~/Downloads/test$ ../loongson-gnu-toolchain-8.3-x86_64-loongarch32r-linux-gnusf-v2.0/bin/loongarch32r-linux-gnusf-readelf ./a.out -a > result_ELF.txt
```

在result_ELF.txt中查看生成的可执行文件信息


## Next

接下来就是配置QEMU模拟器，运行交叉编译的程序。

见文章:[配置QEMU模拟器](./qemu.md)