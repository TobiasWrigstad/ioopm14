CC=gcc
FLAGS=-Wall -ggdb -std=c99

all: test

test: anagram
	@./anagram "clint eastwood" "old west action"
	@./anagram "clint eastwood" "old western action"
	@./anagram "" " "

anagram: anagram.c
	$(CC) $(FLAGS) -o $@ $<

clean:
	rm -f anagram
	rm -rf anagram.dSYM # om du kör på Mac
	rm -f *~

.PHONY: test clean