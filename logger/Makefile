CC=clang
CFLAGS=-Wall -Wextra -pedantic -std=c2x -Iinclude
LDFLAGS=
SRC = src/logger.c
OBJ = build/logger.o

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -v $(OBJ)

.PHONY: all clean
