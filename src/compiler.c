#include "../include/compiler.h"
#include "../include/token.h"
#include "../include/ast.h"
#include <unistd.h>

// Forward declarations of our compiler stages
void scan_wannasmile(const char *source, Token *stream);
ASTNode* parse_wannasmile(Token *stream);
void generate_binary(ASTNode *root, const char *output_name);

void compile_file(const char *source_code, const char *output_binary) {
    write(1, "[COMPILER] Initiating compilation pipeline\n", 43);
    
    // Allocate a fixed token stream capacity for our minimal architecture
    Token token_stream[2048];
    
    // 1. Lexical Analysis Phase
    scan_wannasmile(source_code, token_stream);
    
    // 2. Syntactic Analysis Phase (Parsing into AST)
    ASTNode *root = parse_wannasmile(token_stream);
    
    // 3. Code Generation & ELF Native Wrapping Phase
    if (root) {
        generate_binary(root, output_binary);
    } else {
        write(2, "[COMPILER ERROR] AST generation generated an empty root\n", 56);
    }
}
