CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O0
TARGET = wsmc

SRCS = src/main.c src/lexer.c src/parser.c src/ast.c src/codegen.c src/elf.c src/compiler.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "[SUCCESS] Native wsmc compiler engine successfully built!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

transpile:
	@echo "[TRANSPILER] Compiling via macro engine inside src/engine.h..."
	@echo '#include "src/engine.h"' > temp_build.c
	@cat examples/test.wsm >> temp_build.c
	$(CC) -Wall -Wextra temp_build.c -o wsm_macro_exec
	@rm temp_build.c
	@echo "[SUCCESS] Executable built via macro engine: ./wsm_macro_exec"

clean:
	rm -f src/*.o $(TARGET) output.bin wsm_macro_exec temp_build.c
	@echo "[CLEAN] Removed all generated object files and binaries."

.PHONY: all clean transpile
