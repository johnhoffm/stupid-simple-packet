CC = gcc
CFLAGS = -Wall -std=c11 -O2

default: build

build: encode.c
	$(CC) $(CFLAGS) encode.c -o encode

clean:
	rm -f encode
