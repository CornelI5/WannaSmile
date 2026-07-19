#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOK_INC, TOK_TYPE, TOK_MAIN, TOK_LPAREN, TOK_RPAREN,
    TOK_LBRACE, TOK_RBRACE, TOK_SEMICOLON, TOK_IDENT,
    TOK_STRING, TOK_PRINT, TOK_RETURN, TOK_EOF
} TokenType;

typedef struct {
    TokenType type;
    char value[64];
} Token;

#endif
