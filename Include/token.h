#include "../include/token.h"
#include <unistd.h>

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

        if (source[i] == '[') {
            write(1, "[TOKEN] TOK_LBRACE (Mapped from '[')\n", 37);
            i++;
            continue;
        }
        if (source[i] == ']') {
            write(1, "[TOKEN] TOK_RBRACE (Mapped from ']')\n", 37);
            i++;
            continue;
        }

        // 3. Cek Simbol Tunggal Lainnya
        if (source[i] == '?') {
            write(1, "[TOKEN] TOK_QUESTION (?)\n", 25);
            i++; continue;
        }
        if (source[i] == 'I') {
            write(1, "[TOKEN] TOK_I (I)\n", 18);
            i++; continue;
        }
        if (source[i] == ',') {
            write(1, "[TOKEN] TOK_COMMA (,)\n", 22);
            i++; continue;
        }
        if (source[i] == ':') {
            write(1, "[TOKEN] TOK_COLON (:)\n", 22);
            i++; continue;
        }
        if (source[i] == '-') {
            write(1, "[TOKEN] TOK_MINUS (-)\n", 22);
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
            write(1, "[TOKEN] TOK_CM (cm)\n", 20);
            i += 2;
            continue;
        }
        if (source[i] == 's' && source[i+1] == '(') {
            write(1, "[TOKEN] TOK_S (s)\n", 18);
            i++;
            continue;
        }
        if (source[i] == 'x' && source[i+1] == '(') {
            write(1, "[TOKEN] TOK_X (x)\n", 18);
            i++;
            continue;
        }
        if (source[i] == 't' && (source[i+1] == ' ' || source[i+1] == 'p')) {
            write(1, "[TOKEN] TOK_T (t)\n", 18);
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

        if (source[i] >= '0' && source[i] <= '9') {
            write(1, "[TOKEN] TOK_NUMBER\n", 19);
            while (source[i] >= '0' && source[i] <= '9') i++;
            continue;
        }

        i++; 
    }
    write(1, "[TOKEN] TOK_EOF\n", 16);
}
