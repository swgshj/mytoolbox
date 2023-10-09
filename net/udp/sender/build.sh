#!/bin/bash

# 创建build目录并进入
mkdir -p build
cd build

# 运行CMake生成构建文件
cmake ..

# 使用make编译程序
make

# 返回上级目录
cd ..

