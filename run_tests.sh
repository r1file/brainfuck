#!/bin/bash

# Brainfuck 解释器测试套件

echo "===== Brainfuck 解释器测试 ====="
echo

# 测试1: Hello World
echo "测试1: Hello World"
./brainfuck '++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.'
echo
echo

# 测试2: 打印字母 A
echo "测试2: 打印字母 A"
python3 << 'EOF'
code = '+' * 65 + '.'
import subprocess
subprocess.run(['./brainfuck', code])
EOF
echo
echo

# 测试3: 打印多个字符 ABC
echo "测试3: 打印多个字符 (ABC)"
python3 << 'EOF'
code = ('+' * 65) + '.' + ('>' + '+' * 1 + '<' + '-') * 65
code += '>' + '.' + '>' + ('+' * 1) + '.' + '<' * 2  
# 简化版本
code = '+' * 65 + '.' + '>' + '+' * 66 + '.' + '>' + '+' * 67 + '.'
import subprocess
subprocess.run(['./brainfuck', code])
EOF
echo
echo

# 测试4: 从文件执行
echo "测试4: 从文件执行 (hello.bf)"
./brainfuck hello.bf
echo
echo

# 测试5: 循环测试 - 计算阶乘
echo "测试5: 简单的循环和计算"
python3 << 'EOF'
# 计算 2 + 3 = 5
code = '+' * 2 + '>' + '+' * 3 + '<' + '[>' + '+' + '<-]' + '>' + ('+' * 48) + '.'
import subprocess
subprocess.run(['./brainfuck', code])
EOF
echo
echo

echo "===== 测试完成 ====="
