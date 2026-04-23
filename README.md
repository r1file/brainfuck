# Brainfuck Interpreter

A complete Brainfuck programming language interpreter implemented in C.

## Quick Start

### Compilation
```bash
clang -g brainfuck.c -o brainfuck
# or
gcc -g brainfuck.c -o brainfuck
```

### Execution

**Method 1: Execute code directly**
```bash
./brainfuck '++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.'
```

**Method 2: Execute from file**
```bash
./brainfuck hello.bf
```

## Brainfuck Language Guide

Brainfuck has 8 basic commands that operate on a memory array and a pointer:

| Command | Operation | Description |
|---------|-----------|-------------|
| `>` | Pointer++ | Move data pointer one position to the right |
| `<` | Pointer-- | Move data pointer one position to the left |
| `+` | Value++ | Increment current cell value by 1 (wraps 0-255) |
| `-` | Value-- | Decrement current cell value by 1 (wraps 0-255) |
| `.` | Output | Output ASCII character of current cell value |
| `,` | Input | Read one character into current cell |
| `[` | Loop Start | Jump to matching `]` if current value is 0 |
| `]` | Loop End | Jump to matching `[` if current value is non-zero |

All other characters are ignored, allowing for comments in the code.

## Memory Model

- **Memory Size**: 30,000 bytes (cells)
- **Initial Value**: All cells initialized to 0
- **Data Type**: Unsigned byte (0-255, wrapping)
- **Pointer Range**: 0-29,999 (out of bounds causes error)

## Features

✅ **Complete Command Support** - All 8 standard Brainfuck commands
✅ **Bracket Matching Check** - Automatically detects mismatched `[` and `]`
✅ **Error Handling** - Detects pointer out-of-bounds and bracket errors
✅ **File and CLI Support** - Supports reading from files or passing code directly
✅ **Standard I/O** - Full support for input (`,`) and output (`.`)
✅ **30KB Memory** - Sufficient for running most Brainfuck programs

## Compilation Options

### Debug Mode
```bash
clang -g -O0 brainfuck.c -o brainfuck
```

### Optimized Version
```bash
clang -O2 brainfuck.c -o brainfuck
```

## Testing

The project includes a test script `run_tests.sh` to verify all functionality:

```bash
./run_tests.sh
```

Test Coverage:
- ✅ Hello World program
- ✅ Single character output
- ✅ Multiple character output
- ✅ File execution
- ✅ Loops and calculations

## Frequently Asked Questions

**Q: Why is the output garbled?**
A: Ensure the code passed is correct Brainfuck code with accurate character counts.

**Q: How do I debug a Brainfuck program?**
A: Add comments to your code and analyze the command sequence, or use an online Brainfuck debugger to verify logic.

**Q: Does it support nested loops?**
A: Yes, it supports loops nested to any depth.

**Q: Can the memory be expanded?**
A: Yes, modify the `MEMORY_SIZE` macro in the source code.

## Project Structure

```
.
├── brainfuck.c          # Interpreter source code
├── brainfuck            # Compiled executable
├── hello.bf             # Hello World example
├── hi.bf                # Hi example
├── abc.bf               # ABC output example
├── run_tests.sh         # Automated test script
└── README.md            # This file
```

## References

- [Brainfuck Wikipedia](https://en.wikipedia.org/wiki/Brainfuck)
- [Esolang Brainfuck](https://esolangs.org/wiki/Brainfuck)
- [Try It Online](https://tio.run/#brainfuck) - Online Brainfuck editor

## License

MIT

## Author

r1file

---

**Note**: Brainfuck is a minimalist, Turing-complete programming language designed to demonstrate the possibility of an extremely minimal programming language. While rarely used in practice, it's valuable for learning compiler and interpreter design principles.
