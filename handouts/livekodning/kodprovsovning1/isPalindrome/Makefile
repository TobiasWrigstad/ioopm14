CC=gcc
FLAGS=-Wall -ggdb -std=c99

all: test

test: palindrome
	@./palindrome naturrutan
	@./palindrome naturbarn
	@./palindrome ""

palindrome: palindrome.c
	$(CC) $(FLAGS) -o $@ $<

clean:
	rm -f palindrome
	rm -rf palindrome.dSYM # om du kör på Mac
	rm -f *~

.PHONY: test clean