#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOK_T,          // 't' (Primitive integer data type)
    TOK_T_U,        // 'T U' (Main function entry point)
    TOK_S,          // 's' (Built-in print string function)
    TOK_X,          // 'x' (Built-in process spawning function)
    TOK_CM,         // 'cm' (Return statement / exit status 0)
    TOK_QUESTION,   // '?' (Conditional if statement)
    TOK_I,          // 'I' (Conditional else statement)
    TOK_COLON,      // ':' (Assignment operator)
    TOK_COMMA,      // ',' (Instruction terminator / custom newline)
    TOK_MINUS,      // '-' (Array structure marker)
    TOK_LPAREN,     // '(' (Left parenthesis)
    TOK_RPAREN,     // ')' (Right parenthesis)
    TOK_LBRACE,     // '{' (Left scope brace - internally mapped from '[')
    TOK_RBRACE,     // '}' (Right scope brace - internally mapped from ']')
    TOK_STRING,     // String literal data ("text")
    TOK_NUMBER,     // Numeric literal data (1, 2, 3...)
    TOK_EOF         // End Of File indicator
} TokenType;

typedef struct {
    TokenType type;
    const char *value;
} Token;

#endif
