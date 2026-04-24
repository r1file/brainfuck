# Brainfuck Interpreter Project Explanation

## 1. Introduction

In this project, I implemented a Brainfuck interpreter in C. The program supports all 8 standard Brainfuck commands, and it can run code either from a file or directly from the command line. I also added some basic error handling, such as checking for invalid pointer movement and unmatched brackets.

The main aim of the project was to understand how a simple interpreter works. Even though Brainfuck is a very small language, it still includes important ideas such as memory management, input/output, loops, and command parsing.

## 2. Project Structure

The project contains the following files:

```text
Brainfuck/
├── brainfuck.c
├── run_tests.sh
├── README.md
└── bf_tests/
    ├── test.bf
    ├── test2.bf
    ├── test5.bf
    └── test8.bf
```

- `brainfuck.c` contains the main interpreter code.
- `run_tests.sh` compiles the program and runs the test files.
- `bf_tests/` contains sample Brainfuck programs for testing.
- `README.md` gives general instructions on how to use the project.

## 3. Program Design

The interpreter follows the normal Brainfuck execution model:

- a memory tape of 30,000 cells
- a data pointer to the current memory cell
- an instruction pointer to the current command

The memory tape is stored as an array of `unsigned char`. This is useful because each cell can hold values from `0` to `255`, which matches the usual 8-bit Brainfuck memory model.

To store the current execution state, I used the following structure:

```c
typedef struct {
    unsigned char memory[MEMORY_SIZE];
    int data_ptr;
    int inst_ptr;
    const char *code;
    int code_len;
} BFState;
```

This structure keeps the important runtime information in one place and makes the code easier to manage.

## 4. Implementation

### 4.1 Execution Loop

The main part of the interpreter is the `execute` function. This function initializes the memory, sets both pointers to the starting position, and then reads the source code one character at a time using a `while` loop and a `switch` statement.

Each Brainfuck command has a direct action:

- `>` moves the data pointer right
- `<` moves the data pointer left
- `+` increments the current cell
- `-` decrements the current cell
- `.` outputs the current cell as a character
- `,` reads one character into the current cell
- `[` and `]` implement loops

Any character that is not a Brainfuck command is ignored. This means the source code can still include spaces or line breaks without affecting execution.

### 4.2 Loop Handling

One of the most important parts of the interpreter is handling loops correctly. When the interpreter reaches:

- `[` and the current cell is `0`, execution must jump forward to the matching `]`
- `]` and the current cell is not `0`, execution must jump back to the matching `[`

To do this, the program uses a helper function:

```c
int find_matching_bracket(const char *code, int pos, char open, char close)
```

The function uses a counter to deal with nested loops. It scans through the code until it finds the correct matching bracket. If there is no matching bracket, it returns `-1`, and the program prints an error message.

### 4.3 File Input

The `read_file` function loads the full contents of a Brainfuck file into dynamically allocated memory. It uses:

- `fopen` to open the file
- `fseek` and `ftell` to determine file size
- `malloc` to allocate memory
- `fread` to copy file contents into the buffer

This allows the interpreter to run code from a file in the same way as code entered directly on the command line.

### 4.4 Command-Line Input

The `main` function supports two ways to run the program:

1. run Brainfuck code from a file
2. run Brainfuck code provided directly as a command-line argument

If the first argument is a valid file, the program reads it with `read_file`. Otherwise, it treats that argument as Brainfuck code and executes it directly.

## 5. Error Handling

I added several basic runtime checks:

- moving the data pointer below `0`
- moving the data pointer beyond the memory limit
- unmatched `[` or `]`
- file open failure
- memory allocation failure

These checks help prevent invalid behavior and make it easier to understand what went wrong. Error messages are printed to `stderr`.

## 6. Testing

The project includes a shell script called `run_tests.sh`. This script builds the program if needed and then runs all `.bf` files in the `bf_tests/` directory.

The current test files cover:

- simple output
- multi-character output
- loops and pointer movement
- larger Brainfuck programs

This gives a simple way to check whether the interpreter can run different types of Brainfuck programs correctly.

## 7. Limitations

Although the interpreter works, there are still some limitations:

- bracket matching is performed by scanning the source code during execution, which is simple but not optimal for large programs
- the test script runs programs but does not automatically compare output against expected results
- programs that use the `,` command may require interactive input during testing

These limitations are acceptable for a small student project, but they could be improved in a future version.

## 8. Possible Improvements

There are several ways this project could be improved in the future:

- precompute bracket pairs before execution
- use clearer ownership tracking for dynamically allocated source code
- add automated output checking in the test script
- add a `Makefile` for easier building
- compile with stricter warning flags such as `-Wall -Wextra`

## 9. Conclusion

Overall, this project helped me understand how an interpreter can be built in C using simple logic and data structures. The final program supports the full Brainfuck command set, file input, direct code input, loop handling, and basic testing. Even though Brainfuck is a very small language, implementing it was still a useful exercise in parsing, control flow, and low-level programming.
