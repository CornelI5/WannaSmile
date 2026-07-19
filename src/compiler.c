#include <stdio.h>
#include "../include/lexer.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: wsmc <file.wsm>\n");
        return 1;
    }
    
    printf("Compiling: %s\n", argv[1]);
    return 0;
}
