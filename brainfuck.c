#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 30000

typedef struct {
    unsigned char memory[MEMORY_SIZE];
    int data_ptr;
    int inst_ptr;
    const char *code;
    int code_len;
} BFState;

// 找到匹配的括号
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

// 执行brainfuck代码
void execute(const char *code) {
    BFState state;
    memset(&state.memory, 0, MEMORY_SIZE);
    state.data_ptr = 0;
    state.inst_ptr = 0;
    state.code = code;
    state.code_len = strlen(code);
    
    while (state.inst_ptr < state.code_len) {
        char cmd = code[state.inst_ptr];
        
        switch (cmd) {
            case '>':
                // 指针右移
                state.data_ptr++;
                if (state.data_ptr >= MEMORY_SIZE) {
                    fprintf(stderr, "Error: Data Pointer Out of Range!\n");
                    return;
                }
                break;
                
            case '<':
                // 指针左移
                state.data_ptr--;
                if (state.data_ptr < 0) {
                    fprintf(stderr, "Error: Data Pointer Out of Range!\n");
                    return;
                }
                break;
                
            case '+':
                // 当前值加1
                state.memory[state.data_ptr]++;
                break;
                
            case '-':
                // 当前值减1
                state.memory[state.data_ptr]--;
                break;
                
            case '.':
                // 输出当前值的ASCII字符
                putchar(state.memory[state.data_ptr]);
                break;
                
            case ',':
                // 输入一个字符
                state.memory[state.data_ptr] = getchar();
                break;
                
            case '[':
                // 如果当前值为0，跳转到匹配的]
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
                // 如果当前值非0，跳转到匹配的[
                if (state.memory[state.data_ptr] != 0) {
                    int matching = find_matching_bracket(code, state.inst_ptr, ']', '[');
                    if (matching == -1) {
                        fprintf(stderr, "Error: No Matching [\n");
                        return;
                    }
                    state.inst_ptr = matching;
                }
                break;
                
            default:
                // 忽略其他字符
                break;
        }
        
        state.inst_ptr++;
    }
}

// 从文件读取代码
char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could Not Open File %s\n", filename);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        fprintf(stderr, "Error: Memory Allocation Failed\n");
        fclose(file);
        return NULL;
    }
    
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);
    
    return buffer;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <brainfuck file or code>\n", argv[0]);
        printf("Example:\n");
        printf("  %s code.bf          # Execute code file\n", argv[0]);
        printf("  %s '++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.'  # Execute code directly\n", argv[0]);
        return 1;
    }
    
    char *code = NULL;
    
    // 尝试作为文件打开
    FILE *test = fopen(argv[1], "r");
    if (test) {
        fclose(test);
        code = read_file(argv[1]);
    } else {
        // 直接作为代码执行
        code = argv[1];
    }
    
    if (code) {
        execute(code);
        
        // 如果是从文件读取的，需要释放内存
        if (test != NULL || fopen(argv[1], "r") != NULL) {
            FILE *test2 = fopen(argv[1], "r");
            if (test2) {
                fclose(test2);
                free(code);
            }
        }
    }
    
    return 0;
}