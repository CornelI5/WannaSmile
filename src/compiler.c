#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input.wsm>\n", argv[0]);
        exit(1);
    }

    printf("[!] Initializing WannaSmile Compiler v0.1\n");
    return 0;
}
}
