#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "ast.h"

// Parses the token stream sequentially into an Abstract Syntax Tree (AST)
ASTNode* parse_wannasmile(Token *stream);

#endif
