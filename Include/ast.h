#ifndef AST_H
#define AST_H

#include "token.h"

typedef enum {
    NODE_PROGRAM,
    NODE_FUNCTION,
    NODE_VAR_DECL,
    NODE_IF,
    NODE_PRINT,
    NODE_SPAWN,
    NODE_RETURN
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    const char *value;              // For identifiers, strings, or numbers
    struct ASTNode *left;           // Left child / condition / expression
    struct ASTNode *right;          // Right child / body block
    struct ASTNode *next;           // Next instruction in the sequence (linked list)
} ASTNode;

// Memory allocator for AST Nodes
ASTNode* create_ast_node(ASTNodeType type);

#endif
