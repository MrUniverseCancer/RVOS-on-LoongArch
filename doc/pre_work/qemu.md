# 配置QEMU

> 本文解决配置QEMU模拟器的问题。版本位LA32位的QEMU模拟器。

## 1. 下载QEMU

[一种版本](https://gitee.com/loongson-edu/la32r-QEMU/releases/tag/v0.0.2)

解压缩到指定目录

```shell
tar -xvf xxx
```

## 2. 测试是否可以使用

运行上一个[文档](./cross_toolchain.md)中的程序

```shell
ubuntu@VM8889-huyangjia:~/Downloads/test$ ../la32r-QEMU-x86_64-ubuntu-22.04/qemu-loongarch32 ./a.out 
```

一种发现的报错及解决如下：

```shell
../la32r-QEMU-x86_64-ubuntu-22.04/qemu-loongarch32: error while loading shared libraries: libcapstone.so.4: cannot open shared object file: No such file or directory
```

这个说的是QEMU程序缺少`libcapstone.so.4`库，解决方法如下：

```shell
sudo apt-get install libcapstone4
```

完成后，再次执行，结果如下

```shell
ubuntu@VM8889-huyangjia:~/Downloads/test$ ../la32r-QEMU-x86_64-ubuntu-22.04/qemu-loongarch32 ./a.out 
Hello, World!
```

## end

到目前为止，已经完成了交叉编译工具链和QEMU模拟器的配置，可以进行后续的实验了。

