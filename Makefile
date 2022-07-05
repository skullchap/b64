CC = gcc
CFLAGS = -I. -O3 -Werror -Wpedantic

test: tests/basic.c
	@$(CC) tests/basic.c $(CFLAGS) -o basic
	@./basic
	@rm ./basic

default: test

all: test
