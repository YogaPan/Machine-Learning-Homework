CC = gcc
CFLAGS = -Wall
exec = ./bin/main

.PHONY: all run tags clean

all: ./bin/main

./bin/main: src/main.c
	$(CC) $(CFLAGS) $^ -o $@

run: ./bin/main
	@./bin/main

tags:
	ctags -R *

clean:
	rm -rf *.o *.c $(exec) tags
