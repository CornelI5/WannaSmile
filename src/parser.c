#include "../include/token.h"
#include "../include/ast.h"
#include <unistd.h>
#include <stdlib.h>

// Global array or stream pointer of tokens from lexer
static Token *token_stream;
static int token_index = 0;

// Helper to write error logs in raw English
static void parser_error(const char *msg) {
    int len = 0;
    while (msg[len] != '\0') len++;
    write(2, "[PARSER ERROR] ", 15);
    write(2, msg, len);
    write(2, "\n", 1);
    exit(1);
}

static Token advance() {
    return token_stream[token_index++];
}

static Token peek() {
    return token_stream[token_index];
}

static void consume(TokenType type, const char *err_msg) {
    if (peek().type == type) {
        advance();
    } else {
        parser_error(err_msg);
    }
}

// Forward declaration of statement parsing
ASTNode* parse_statement();

// Parsing the function body enclosed in [ ... ]
ASTNode* parse_block() {
    consume(TOK_LBRACE, "Expected '[' to open the block scope.");
    write(1, "[PARSER] Entering block scope\n", 31);
    
    ASTNode *head = NULL;
    ASTNode *current = NULL;
    
    while (peek().type != TOK_RBRACE && peek().type != TOK_EOF) {
        ASTNode *stmt = parse_statement();
        if (stmt) {
            if (!head) {
                head = stmt;
                current = head;
            } else {
                current->next = stmt;
                current = current->next;
            }
        }
    }
    
    consume(TOK_RBRACE, "Expected ']' to close the block scope.");
    write(1, "[PARSER] Exiting block scope\n", 30);
    return head;
}

// Parsing individual statements separated by commas ','
ASTNode* parse_statement() {
    Token t = peek();
    
    // 1. Conditional structure ?(cond) [ body ]
    if (t.type == TOK_QUESTION) {
        advance(); // consume '?'
        ASTNode *node = create_ast_node(NODE_IF);
        write(1, "[PARSER] Processing TOK_QUESTION conditional\n", 46);
        
        consume(TOK_LPAREN, "Expected '(' after '?'.");
        // For simplicity, skip parsing expression inside condition for now
        while(peek().type != TOK_RPAREN && peek().type != TOK_EOF) advance();
        consume(TOK_RPAREN, "Expected ')' after condition.");
        
        node->left = parse_block(); // Main branch body
        
        // Handle optional 'I' (else) block
        if (peek().type == TOK_I) {
            advance(); // consume 'I'
            write(1, "[PARSER] Processing TOK_I else branch\n", 38);
            node->right = parse_block();
        }
        
        if (peek().type == TOK_COMMA) advance(); // consume ',' terminator
        return node;
    }
    
    // 2. Print operation s("text"),
    if (t.type == TOK_S) {
        advance();
        ASTNode *node = create_ast_node(NODE_PRINT);
        write(1, "[PARSER] Processing TOK_S statement\n", 36);
        consume(TOK_LPAREN, "Expected '(' before string literal.");
        
        Token str_tok = advance();
        if (str_tok.type != TOK_STRING) parser_error("Expected string literal inside print function.");
        node->value = str_tok.value;
        
        consume(TOK_RPAREN, "Expected ')' after string literal.");
        consume(TOK_COMMA, "Expected ',' as instruction terminator.");
        return node;
    }

    // 3. Process spawning x("cmd"),
    if (t.type == TOK_X) {
        advance();
        ASTNode *node = create_ast_node(NODE_SPAWN);
        write(1, "[PARSER] Processing TOK_X statement\n", 36);
        consume(TOK_LPAREN, "Expected '(' before command string.");
        
        Token cmd_tok = advance();
        node->value = cmd_tok.value;
        
        consume(TOK_RPAREN, "Expected ')' after command string.");
        consume(TOK_COMMA, "Expected ',' as instruction terminator.");
        return node;
    }

    // 4. Return control cm,
    if (t.type == TOK_CM) {
        advance();
        ASTNode *node = create_ast_node(NODE_RETURN);
        write(1, "[PARSER] Processing TOK_CM return state\n", 40);
        consume(TOK_COMMA, "Expected ',' as instruction terminator.");
        return node;
    }

    // Variable declaration: t p : 1,
    if (t.type == TOK_T) {
        advance();
        ASTNode *node = create_ast_node(NODE_VAR_DECL);
        write(1, "[PARSER] Processing TOK_T declaration\n", 38);
        
        Token ident = advance(); // get variable name
        node->value = ident.value;
        
        consume(TOK_COLON, "Expected ':' for value assignment.");
        advance(); // skip value for basic structure
        consume(TOK_COMMA, "Expected ',' as instruction terminator.");
        return node;
    }

    advance(); // Fallback to avoid infinite loops
    return NULL;
}

// Global Parser Entry
ASTNode* parse_wannasmile(Token *stream) {
    token_stream = stream;
    token_index = 0;
    
    write(1, "[PARSER] Beginning syntactic structural analysis\n", 49);
    
    // Root program check for 'T U' entry point
    consume(TOK_T_U, "Fatal: Missing program entry point 'T U()'.");
    consume(TOK_LPAREN, "Expected '(' after main entry.");
    consume(TOK_RPAREN, "Expected ')' after main entry.");
    
    ASTNode *root = create_ast_node(NODE_FUNCTION);
    root->value = "main";
    root->left = parse_block(); // Parse the root logic within the program scope
    
    write(1, "[PARSER] Syntactic compilation successful\n", 42);
    return root;
}
