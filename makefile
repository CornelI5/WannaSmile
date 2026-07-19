CC = gcc
CFLAGS = -Iinclude
SRC = src/*.c
OBJ = $(SRC:.c=.o)

wsmc: $(OBJ)
	$(CC) -o wsmc $(OBJ)

clean:
	rm -f src/*.o wsmc
