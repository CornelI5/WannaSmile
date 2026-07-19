#include "../include/ast.h"
#include <stdlib.h>

ASTNode* create_ast_node(ASTNodeType type) {
    // Standard allocation but initialized to clean state
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        return NULL; // Out of memory
    }
    node->type = type;
    node->value = NULL;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}
