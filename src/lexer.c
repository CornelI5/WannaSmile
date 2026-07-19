#include "token.h"
#include <unistd.h>

int str_compare(const char *s1, const char *s2, int n) {
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) return 0;
    }
    return 1;
}

void scan_wannasmile(const char *source) {
    int i = 0;
    while (source[i] != '\0') {
        if (source[i] == ' ' || source[i] == '\t' || source[i] == '\n') {
            i++;
            continue;
        }

        if (source[i] == 'T' && source[i+1] == ' ' && source[i+2] == 'U') {
            write(1, "[TOKEN] TOK_T_U (int main)\n", 27);
            i += 3;
            continue;
        }

        if (source[i] == '?') {
            write(1, "[TOKEN] TOK_QUESTION (if)\n", 26);
            i++; continue;
        }
        if (source[i] == 'I') {
            write(1, "[TOKEN] TOK_I (else)\n", 21);
            i++; continue;
        }
        if (source[i] == ',') {
            write(1, "[TOKEN] TOK_COMMA (newline/terminator)\n", 39);
            i++; continue;
        }
        if (source[i] == ':') {
            write(1, "[TOKEN] TOK_COLON (=)\n", 22);
            i++; continue;
        }
        if (source[i] == '-') {
            write(1, "[TOKEN] TOK_MINUS (array)\n", 26);
            i++; continue;
        }
        if (source[i] == '{') {
            write(1, "[TOKEN] TOK_LBRACE\n", 19);
            i++; continue;
        }
        if (source[i] == '}') {
            write(1, "[TOKEN] TOK_RBRACE\n", 19);
            i++; continue;
        }
        if (source[i] == '(') {
            write(1, "[TOKEN] TOK_LPAREN\n", 19);
            i++; continue;
        }
        if (source[i] == ')') {
            write(1, "[TOKEN] TOK_RPAREN\n", 19);
            i++; continue;
        }

        if (source[i] == 'c' && source[i+1] == 'm') {
            write(1, "[TOKEN] TOK_CM (return 0)\n", 26);
            i += 2;
            continue;
        }
        if (source[i] == 's' && (source[i+1] == '(' || source[i+1] == ' ')) {
            write(1, "[TOKEN] TOK_S (print)\n", 22);
            i++;
            continue;
        }
        if (source[i] == 'x' && (source[i+1] == '(' || source[i+1] == ' ')) {
            write(1, "[TOKEN] TOK_X (spawn)\n", 22);
            i++;
            continue;
        }
        if (source[i] == 't' && (source[i+1] == ' ' || source[i+1] == 'I' || source[i+1] == 'p')) {
            write(1, "[TOKEN] TOK_T (int type)\n", 25);
            i++;
            continue;
        }

        if (source[i] == '"') {
            write(1, "[TOKEN] TOK_STRING\n", 19);
            i++;
            while (source[i] != '"' && source[i] != '\0') i++;
            if (source[i] == '"') i++;
            continue;
        }

        i++;
    }
    write(1, "[TOKEN] TOK_EOF\n", 16);
}
