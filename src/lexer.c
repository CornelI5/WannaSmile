#include "../include/token.h"
#include <unistd.h>

void scan_wannasmile(const char *source) {
    int i = 0;
    while (source[i] != '\0') {
        // Skip whitespaces except commas (since comma is your custom newline/terminator)
        if (source[i] == ' ' || source[i] == '\t' || source[i] == '\n') {
            i++;
            continue;
        }

        // 1. Check 'T U' (Main Entry Function)
        if (source[i] == 'T' && source[i+1] == ' ' && source[i+2] == 'U') {
            write(1, "[LEXER] Found TOK_T_U (main entry)\n", 35);
            i += 3;
            continue;
        }

        // 2. Map brackets '[' and ']' directly to braces internally
        if (source[i] == '[') {
            write(1, "[LEXER] Found TOK_LBRACE (mapped from '[')\n", 43);
            i++;
            continue;
        }
        if (source[i] == ']') {
            write(1, "[LEXER] Found TOK_RBRACE (mapped from ']')\n", 43);
            i++;
            continue;
        }

        // 3. Single character structural tokens
        if (source[i] == '?') {
            write(1, "[LEXER] Found TOK_QUESTION (conditional if)\n", 44);
            i++; continue;
        }
        if (source[i] == 'I') {
            write(1, "[LEXER] Found TOK_I (conditional else)\n", 39);
            i++; continue;
        }
        if (source[i] == ',') {
            write(1, "[LEXER] Found TOK_COMMA (instruction terminator)\n", 49);
            i++; continue;
        }
        if (source[i] == ':') {
            write(1, "[LEXER] Found TOK_COLON (assignment/separator)\n", 47);
            i++; continue;
        }
        if (source[i] == '-') {
            write(1, "[LEXER] Found TOK_MINUS (array marker)\n", 39);
            i++; continue;
        }
        if (source[i] == '(') {
            write(1, "[LEXER] Found TOK_LPAREN\n", 25);
            i++; continue;
        }
        if (source[i] == ')') {
            write(1, "[LEXER] Found TOK_RPAREN\n", 25);
            i++; continue;
        }

        // 4. WannaSmile Core Keywords ('cm', 's', 'x', 't')
        if (source[i] == 'c' && source[i+1] == 'm') {
            write(1, "[LEXER] Found TOK_CM (return exit success)\n", 43);
            i += 2;
            continue;
        }
        if (source[i] == 's' && source[i+1] == '(') {
            write(1, "[LEXER] Found TOK_S (print output)\n", 35);
            i++;
            continue;
        }
        if (source[i] == 'x' && source[i+1] == '(') {
            write(1, "[LEXER] Found TOK_X (spawn process)\n", 36);
            i++;
            continue;
        }
        if (source[i] == 't' && (source[i+1] == ' ' || source[i+1] == 'p')) {
            write(1, "[LEXER] Found TOK_T (primitive primitive type)\n", 47);
            i++;
            continue;
        }

        // 5. String Literals
        if (source[i] == '"') {
            write(1, "[LEXER] Found TOK_STRING (literal value)\n", 41);
            i++;
            while (source[i] != '"' && source[i] != '\0') i++;
            if (source[i] == '"') i++;
            continue;
        }

        // 6. Numeric Literals
        if (source[i] >= '0' && source[i] <= '9') {
            write(1, "[LEXER] Found TOK_NUMBER (integer value)\n", 41);
            while (source[i] >= '0' && source[i] <= '9') i++;
            continue;
        }

        // Skip unknown character to avoid compiler panic
        i++;
    }
    write(1, "[LEXER] Reached TOK_EOF (end of file parsing)\n", 46);
}
