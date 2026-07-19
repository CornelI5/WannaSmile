#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOK_T,          // 't' 
    TOK_T_U,        // 'T U' 
    TOK_S,          // 's' 
    TOK_X,          // 'x' 
    TOK_CM,         // 'cm' 
    TOK_QUESTION,   // '?' 
    TOK_I,          // 'I' 
    TOK_COLON,      // ':' 
    TOK_COMMA,      // ',' 
    TOK_MINUS,      // '-' 
    TOK_LPAREN,     // '('
    TOK_RPAREN,     // ')'
    TOK_LBRACE,     // '{'
    TOK_RBRACE,     // '}'
    TOK_STRING,     // "text"
    TOK_NUMBER,     // 1, 2, 3
    TOK_EOF
} TokenType;

typedef struct {
    TokenType type;
    const char *value;
} Token;

#endif
