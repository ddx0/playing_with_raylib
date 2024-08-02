CC=clang
CFLAGS=-Wall -Wextra -pedantic -std=c2x
SRC = src/main.c
OBJ = build/main.o
EXE_DIR = ../bin
EXE_NAME = main
LIB_DIR = ../logger
LIB_OBJ = $(LIB_DIR)/build/logger.o
PKG_LIBS = raylib
CFLAGS += $(shell pkg-config --cflags $(PKG_LIBS))
LDFLAGS += $(shell pkg-config --libs $(PKG_LIBS))

all: $(LIB_OBJ) $(EXE_NAME)

$(LIB_OBJ):
	$(MAKE) -C $(LIB_DIR)

$(EXE_NAME): $(OBJ) $(LIB_OBJ)
	$(CC) -o $(EXE_DIR)/$@ $^ $(LDFLAGS)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -v $(OBJ)

.PHONY: all clean