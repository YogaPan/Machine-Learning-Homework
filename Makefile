CC = gcc
CFLAGS = -Wall
exec = ./executable/main

.PHONY: all run tags clean

all: ./executable/main

./executable/main: source/main.c
	@$(CC) $(CFLAGS) $^ -o $@

run: ./executable/main
	@$(exec)

tags:
	ctags -R *

clean:
	rm -rf *.o *.c $(exec) tags
