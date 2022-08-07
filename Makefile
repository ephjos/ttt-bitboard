.POSIX:
CC     = gcc
CFLAGS = -Wall -O3 -g
LDLIBS = -lm
PREFIX = /usr/local

all: ttt-bitboard
ttt-bitboard: main.o
	$(CC) $(LDFLAGS) -o ttt-bitboard main.o $(LDLIBS)
main.o: main.c
clean:
	rm -f ttt-bitboard main.o
