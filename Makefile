CC = gcc
CFLAGS = -Wall
exec = main

.PHONY: all tags clean

all: $(exec)

main: src/main.c
	$(CC) $(CFLAGS) $^ -o $@

tags:
	ctags -R *

clean:
	rm -rf *.o *.c $(exec) tags
