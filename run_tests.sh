#!/bin/bash

# Brainfuck Interpreter Test Suite

echo "===== Brainfuck Interpreter Tests ====="
echo

# Test 1: Hello World
echo "Test 1: Hello World"
./brainfuck '++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.'
echo
echo

# Test 2: Print Letter A
echo "Test 2: Print Letter A"
python3 << 'EOF'
code = '+' * 65 + '.'
import subprocess
subprocess.run(['./brainfuck', code])
EOF
echo
echo

# Test 3: Print Multiple Characters (ABC)
echo "Test 3: Print Multiple Characters (ABC)"
python3 << 'EOF'
code = ('+' * 65) + '.' + ('>' + '+' * 1 + '<' + '-') * 65
code += '>' + '.' + '>' + ('+' * 1) + '.' + '<' * 2  
# Simplified version
code = '+' * 65 + '.' + '>' + '+' * 66 + '.' + '>' + '+' * 67 + '.'  # ABC
import subprocess
subprocess.run(['./brainfuck', code])
EOF
echo
echo

# Test 4: Execute from File
echo "Test 4: Execute from File (hello.bf)"
./brainfuck hello.bf
echo
echo

# Test 5: Loop Test - Calculate Factorial
echo "Test 5: Simple Loop and Calculation"
python3 << 'EOF'
# Calculate 2 + 3 = 5
code = '+' * 2 + '>' + '+' * 3 + '<' + '[>' + '+' + '<-]' + '>' + ('+' * 48) + '.'
import subprocess
subprocess.run(['./brainfuck', code])
EOF
echo
echo

echo "===== Tests Completed ====="
