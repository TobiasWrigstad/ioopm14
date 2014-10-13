CC=gcc
FLAGS=-Wall -ggdb -std=c99
VECTOR_DEPS=vector.c vector.h

all: test

test: test.c vector.o
	$(CC) $(FLAGS) -o $@ $< vector.o
	./$@

vector.o: $(VECTOR_DEPS)
	$(CC) $(FLAGS) -c $< -lm

clean:
	rm -f test vector.o
	rm -rf test.dSYM # om du kör på Mac
	rm -f *~

.PHONY: test clean