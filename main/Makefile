CC=clang
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c2x -g -fsanitize=address -I../liblogger/include
LDFLAGS := -fsanitize=address -L../liblogger/build/bin
LDLIBS := -llogger
LIB := ../liblogger/build/bin/liblogger.a

BUILD_DIR := build
SRC_DIR := src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR := $(BUILD_DIR)/obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BIN_DIR := $(BUILD_DIR)/bin
BIN := $(BIN_DIR)/main

PKG_LIBS = raylib
CFLAGS += $(shell pkg-config --cflags $(PKG_LIBS))
LDFLAGS += $(shell pkg-config --libs $(PKG_LIBS))

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ) | $(BIN_DIR) $(LIB)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(LIB):
	$(MAKE) -C ../liblogger

$(OBJ): $(SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	$(MAKE) -C ../liblogger clean
	rm -frv $(OBJ_DIR) $(BIN_DIR)
