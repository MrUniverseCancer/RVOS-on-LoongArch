# switch出现的奇怪问题

## 问题描述

在移植 `printf` 的时候，发现有如下现象

1. `uart_puts` 函数可以正常输出字符串
2. `printf` 函数在没有格式串的情况下可以正常输出字符串
3. `printf` 函数在有格式串的情况下，会**反复输出**从 `start_kernel` 函数开始到格式串前面的所有的字符串

## 问题分析

参照 `0dd6a771d90ce1b81e9420881ff48a514cb6a646` 版本的设计和debug思想，发现问题出现在switch的跳跃。

当switch的**分支**超过5个，在loongarch的编译器中使用 `jirl` 语句实现 