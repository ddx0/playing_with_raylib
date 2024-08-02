CC=clang
CFLAGS=-Wall -Wextra -pedantic -std=c2x

BUILD_DIR=./build

logger.o: logger.c
	$(CC) -c -o $(BUILD_DIR)/$@ $< $(CFLAGS)

.PHONY: all
all: logger.o

.PHONY: clean
clean:
	rm -v $(BUILD_DIR)/*