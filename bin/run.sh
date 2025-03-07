#!/bin/bash

# 设置编译器
CC=gcc

# 设置输出文件
OUTFILE=main.out

# 编译 C 代码
$CC -o $OUTFILE *.c

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running program..."
    echo "----------------------------------------"
    ./$OUTFILE  # 运行程序
else
    echo "Compilation failed."
fi

