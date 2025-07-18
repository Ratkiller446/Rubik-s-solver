# Rubik's Cube Auto-Solver Makefile

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
LDFLAGS =
SRC_DIR = .
OBJ_DIR = ../build
BIN = ../build/rubicks

SRCS = main.c cube.c moves.c display.c input.c utils.c solver.c
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
HEADERS = cube.h moves.h display.h input.h utils.h solver.h

.PHONY: all debug release clean install

all: release

debug: CFLAGS += -g -O0 -DDEBUG
debug: $(BIN)

release: CFLAGS += -O2
release: $(BIN)

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN)

install: $(BIN)
	install -m 755 $(BIN) /usr/local/bin/ 