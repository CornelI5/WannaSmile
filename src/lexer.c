#include "../include/token.h"
#include <stdio.h>

void next_token(FILE *f) {
    char c;
    while ((c = fgetc(f)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') continue;
        
        switch(c) {
            case '#': printf("TOKEN_HASH\n"); break;
            case 'T': printf("TOKEN_TYPE\n"); break;
            case 'U': printf("TOKEN_MAIN\n"); break;
            case 's': printf("TOKEN_PRINT\n"); break;
            case ']': printf("TOKEN_CLOSE\n"); break;
            default: break;
        }
    }
}
