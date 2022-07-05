CC = gcc
CFLAGS = -I. -O3 -Werror -Wpedantic -std=c89

test: tests/basic.c
	@$(CC) tests/basic.c $(CFLAGS) -o basic
	@./basic
	@rm ./basic

default: test

all: test
