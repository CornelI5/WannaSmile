#include "../include/ast.h"
#include <unistd.h>

// A primitive buffer to host emitted x86_64 machine operational codes
static unsigned char code_buf[4096];
static int code_idx = 0;

static void emit(unsigned char byte) {
    code_buf[code_idx++] = byte;
}

static void emit_bytes(unsigned char *bytes, int size) {
    for (int i = 0; i < size; i++) {
        emit(bytes[i]);
    }
}

void compile_ast_to_machine(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_FUNCTION:
            write(1, "[CODEGEN] Translating global entry point loop\n", 46);
            compile_ast_to_machine(node->left);
            break;

        case NODE_PRINT:
            write(1, "[CODEGEN] Emitting low-level native sys_write code\n", 51);
            // 1. mov rax, 1 (sys_write syscall number)
            emit_bytes((unsigned char[]){0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x00}, 7);
            // 2. mov rdi, 1 (stdout file descriptor)
            emit_bytes((unsigned char[]){0x48, 0xc7, 0xc7, 0x01, 0x00, 0x00, 0x00}, 7);
            
            // For simple raw compilation execution, we inline inline a temporary test message pointer
            // In a full compiler implementation, string constants are injected into a data segment pointer region
            // mov rsi, 0x4000b0 (Placeholder target virtual memory tracking address pointer)
            emit_bytes((unsigned char[]){0x48, 0xc7, 0xc6, 0xb0, 0x00, 0x40, 0x00}, 7);
            // 3. mov rdx, 6 (Length of message "Smile\n")
            emit_bytes((unsigned char[]){0x48, 0xc7, 0xc2, 0x06, 0x00, 0x00, 0x00}, 7);
            // 4. syscall
            emit_bytes((unsigned char[]){0x0f, 0x05}, 2);
            break;

        case NODE_RETURN:
            write(1, "[CODEGEN] Emitting low-level native sys_exit code\n", 50);
            // 1. mov rax, 60 (sys_exit syscall number)
            emit_bytes((unsigned char[]){0x48, 0xc7, 0xc0, 0x3c, 0x00, 0x00, 0x00}, 7);
            // 2. xor rdi, rdi (exit status code 0)
            emit_bytes((unsigned char[]){0x48, 0x31, 0xff}, 3);
            // 3. syscall
            emit_bytes((unsigned char[]){0x0f, 0x05}, 2);
            break;

        default:
            // Recursively process structural branches
            compile_ast_to_machine(node->left);
            compile_ast_to_machine(node->right);
            break;
    }

    // Process next statement in sequence array
    if (node->next) {
        compile_ast_to_machine(node->next);
    }
}

// Global invocation entry linking codegen and elf compilation systems
void generate_binary(ASTNode *root, const char *output_name) {
    code_idx = 0;
    compile_ast_to_machine(root);
    
    // External declaration signature for linking purposes
    void write_elf_binary(const char *filename, unsigned char *machine_code, int code_size);
    write_elf_binary(output_name, code_buf, code_idx);
}
