CC = clang

SRC_DIR := logger
SRC_BASE := $(SRC_DIR)/base
SRC_MSG := $(SRC_DIR)/messaging
SRC_TS := $(SRC_DIR)/timestamp
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin

SRC := $(wildcard $(SRC_DIR)/*.c)
SRC += $(wildcard $(SRC_BASE)/*.c)
SRC += $(wildcard $(SRC_MSG)/*.c)
SRC += $(wildcard $(SRC_TS)/*.c)
BIN := $(BIN_DIR)/liblogger.a
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
OBJ += $(patsubst $(SRC_BASE)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_BASE)/*.c))
OBJ += $(patsubst $(SRC_MSG)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_MSG)/*.c))
OBJ += $(patsubst $(SRC_TS)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_TS)/*.c))

CPPFLAGS := -MMD -MP
CFLAGS := -Wall -Wextra -Werror -Wno-gnu-statement-expression-from-macro-expansion -pedantic -std=c2x -g -fsanitize=address -Iinclude -Ilogger
LDFLAGS=
LDLIBS=

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ) | $(BIN_DIR)
	ar -rcvs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(SRC_BASE)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(SRC_MSG)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(SRC_TS)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	rm -frv $(OBJ_DIR) $(BIN_DIR)

-include $(OBJ:.o=.d)
