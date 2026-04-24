#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 30000

typedef struct {
    unsigned char memory[MEMORY_SIZE];  // Memory array for Brainfuck data
    int data_ptr;                       // Data pointer index
    int inst_ptr;                       // Instruction pointer index
    const char *code;                   // Pointer to the Brainfuck code string
    int code_len;                       // Length of the code string
} BFState;

// Find the matching bracket for the given position in Brainfuck code
int find_matching_bracket(const char *code, int pos, char open, char close) {
    int count = 1;
    int direction = (open == '[') ? 1 : -1;
    int start = pos + direction;
    
    while (start >= 0 && start < strlen(code) && count > 0) {
        if (code[start] == open) {
            count++;
        } else if (code[start] == close) {
            count--;
        }
        if (count > 0) {
            start += direction;
        }
    }
    
    return (count == 0) ? start : -1;
}

// Execute the Brainfuck code by interpreting each command in the code string.
void execute(const char *code) {
    BFState state;
    memset(&state.memory, 0, MEMORY_SIZE);
    state.data_ptr = 0;
    state.inst_ptr = 0;
    state.code = code;
    state.code_len = strlen(code);
    // Initializes a BFState struct, sets up memory, data pointer, instruction pointer, etc.
    while (state.inst_ptr < state.code_len) { // Main loop processes each character in the code:
        char cmd = code[state.inst_ptr];
        
        switch (cmd) {
            case '>':
                // - '>' : Increment data pointer, check bounds
                state.data_ptr++;
                if (state.data_ptr >= MEMORY_SIZE) {
                    fprintf(stderr, "Error: Data Pointer Out of Range!\n");
                    return;
                }
                break;
                
            case '<':
                // - '<' : Decrement data pointer, check bounds
                state.data_ptr--;
                if (state.data_ptr < 0) {
                    fprintf(stderr, "Error: Data Pointer Out of Range!\n");
                    return;
                }
                break;
                
            case '+':
                // - '+' : Increment value at current memory location
                state.memory[state.data_ptr]++;
                break;
                
            case '-':
                // - '-' : Decrement value at current memory location
                state.memory[state.data_ptr]--;
                break;
                
            case '.':
                // - '.' : Output ASCII character of current value
                putchar(state.memory[state.data_ptr]);
                break;
                
            case ',':
                // - ',' : Read input character into current location
                state.memory[state.data_ptr] = getchar();
                break;
                
            case '[':
                // - '[' : If current value is 0, jump to matching ']')
                if (state.memory[state.data_ptr] == 0) {
                    int matching = find_matching_bracket(code, state.inst_ptr, '[', ']');
                    if (matching == -1) {
                        fprintf(stderr, "Error: No Matching ]\n");
                        return;
                    }
                    state.inst_ptr = matching;
                }
                break;
                
            case ']':
                // - ']' : If current value is not 0, jump to matching '['
                if (state.memory[state.data_ptr] != 0) {
                    int matching = find_matching_bracket(code, state.inst_ptr, ']', '[');
                    if (matching == -1) {
                        fprintf(stderr, "Error: No Matching [\n");
                        return;
                    }
                    state.inst_ptr = matching;
                }
                break;
            // Handles loops using find_matching_bracket, with error checking for unmatched brackets and pointer out of bounds.
            default:
                // - Others: Ignore
                break;
        }
        
        state.inst_ptr++;
    }
}

// Read the entire content of a file and return it as a dynamically allocated string.
char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");    // Open file in read mode
    if (!file) {
        fprintf(stderr, "Error: Could Not Open File %s\n", filename);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);              // Seek to end of file
    long file_size = ftell(file);          // Get file size
    fseek(file, 0, SEEK_SET);              // Reset to beginning of file
    
    char *buffer = (char *)malloc(file_size + 1);  // Allocate memory (file_size + 1 for null terminator)
    if (!buffer) {
        fprintf(stderr, "Error: Memory Allocation Failed\n");
        fclose(file);
        return NULL;
    }
    
    fread(buffer, 1, file_size, file);     // Read file content into buffer
    buffer[file_size] = '\0';              // Add null terminator to make it a valid C string
    fclose(file);                          // Close the file
    
    return buffer;                         // Return pointer to allocated buffer
}

// Main entry point for the Brainfuck interpreter.
int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Check if at least one argument is provided
        printf("Usage: %s <brainfuck file or code>\n", argv[0]);
        printf("Example:\n");
        printf("  %s code.bf          # Execute code file\n", argv[0]);
        printf("  %s '++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.'  # Execute code directly\n", argv[0]);
        return 1;
    }
    
    char *code = NULL;
    
    // Attempt to open the argument as a file
    FILE *test = fopen(argv[1], "r");
    if (test) {
        // If file exists, close temporary file pointer and read the file content
        fclose(test);
        code = read_file(argv[1]);
    } else {
        // If file doesn't exist, treat argument as direct Brainfuck code
        code = argv[1];
    }
    
    if (code) {
        // Execute the Brainfuck code
        execute(code);
        
        // If code was read from a file, free the allocated memory
        if (test != NULL || fopen(argv[1], "r") != NULL) {
            FILE *test2 = fopen(argv[1], "r");
            if (test2) {
                fclose(test2);
                free(code);  // Free memory only if it was allocated by read_file()
            }
        }
    }
    
    return 0;
}