#include "../include/token.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void lexer(char* source) {
    int i = 0;
    while (source[i] != '\0') {
        if (strncmp(&source[i], "#inc", 4) == 0) {
            printf("TOKEN: INCLUDE\n");
            i += 4;
        } else if (source[i] == 'T') {
            printf("TOKEN: TYPE\n");
            i++;
        } else if (source[i] == 'U') {
            printf("TOKEN: MAIN\n");
            i++;
        } else if (source[i] == ']') {
            printf("TOKEN: RBRACE\n");
            i++;
        } else {
            i++;
        }
    }
}
