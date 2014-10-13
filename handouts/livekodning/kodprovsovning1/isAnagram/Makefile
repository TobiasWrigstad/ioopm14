CC=gcc
FLAGS=-Wall -ggdb -std=c99

all: test

test: anagram
	@./anagram silent listen
	@./anagram silent loud
	@./anagram "" ""
	@./anagram "" nothing

anagram: anagram.c
	$(CC) $(FLAGS) -o $@ $<

clean:
	rm -f anagram
	rm -rf anagram.dSYM # om du kör på Mac
	rm -f *~

.PHONY: test clean