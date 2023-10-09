#!/bin/bash

# 检查参数是否正确
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <port>"
    exit 1
fi

# 设置端口号
PORT="$1"

# 运行编译后的程序
./build/udp_receiver "$PORT"

