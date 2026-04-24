#!/bin/bash

# Brainfuck Interpreter Test Suite
set -e

if [ ! -x ./brainfuck ]; then
  echo "Building brainfuck executable..."
  clang -g brainfuck.c -o brainfuck
fi

if [ ! -d bf_tests ]; then
  echo "Error: bf_tests directory not found"
  exit 1
fi

echo "===== Brainfuck Interpreter Tests ====="
echo

shopt -s nullglob
files=(bf_tests/*.bf)
if [ ${#files[@]} -eq 0 ]; then
  echo "Error: No .bf files found in bf_tests"
  exit 1
fi

for testfile in "${files[@]}"; do
  echo "Running test: $testfile"
  ./brainfuck "$testfile"
  echo
done

echo "===== Tests Completed ====="
