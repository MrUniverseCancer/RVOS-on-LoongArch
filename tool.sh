#!/bin/bash

# 定义端口号
PORT=1234

# 使用lsof查找占用该端口的进程ID
PID=$(lsof -i tcp:$PORT | grep 'LISTEN' | awk '{print $2}')

# 检查是否找到了PID
if [ -z "$PID" ]; then
    echo "没有找到占用端口$PORT的进程。"
    exit 1
fi

# 杀死找到的进程
kill $PID

# 检查是否成功杀死了进程
if [ $? -eq 0 ]; then
    echo "成功结束了占用端口$PORT的进程，PID是$PID。"
else
    echo "结束进程失败。"
fi
