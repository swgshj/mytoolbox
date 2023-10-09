#!/bin/bash

# 检查参数是否正确
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <IP> <port> <message>"
    exit 1
fi

# 设置参数
IP="$1"
PORT="$2"
MESSAGE="$3"

# 运行编译后的程序
./build/udp_sender "$IP" "$PORT" "$MESSAGE"

