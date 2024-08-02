CC=clang
CFLAGS=-Wall -Wextra -pedantic -std=c2x
BUILD_DIR=./build

PKG_LIBS = raylib
CFLAGS += $(shell pkg-config --cflags $(PKG_LIBS))
LDFLAGS += $(shell pkg-config --libs $(PKG_LIBS))

LOGGER_LIB = ./logger/build/logger.o

main: main.o
	$(CC) -o $(BUILD_DIR)/$@ $(BUILD_DIR)/$^ $(LOGGER_LIB) $(LDFLAGS)

main.o: main.c
	$(CC) -c -o $(BUILD_DIR)/$@ $< $(CFLAGS)

.PHONY: all
all:
	pushd . && cd logger && make $@ && popd
	make main

.PHONY: clean
clean:
	rm -v $(BUILD_DIR)/*

.PHONY: cleanall
cleanall: clean
	cd logger && make clean