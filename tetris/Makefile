.PHONY: clean

OBJ=obj/main.o \
		obj/def.o \
		obj/tetris.o  \
		obj/keyboard.o 

CC=gcc
CFLAGS=-g  -I ./include  -std=gnu99

all : bin/tetris bin/cli

bin/tetris: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

bin/cli : obj/def.o obj/tetris.o  obj/cli.o obj/keyboard.o
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o : src/%.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -rf obj/*

