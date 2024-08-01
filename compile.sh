#!/bin/zsh

BUILD_DIR="./build"
PROG_NAME="main"
SRC_FILES="main.c"

eval clang -Wall -Wextra -pedantic -std=c2x $SRC_FILES $(pkg-config --libs --cflags raylib) -o "$BUILD_DIR/$PROG_NAME"