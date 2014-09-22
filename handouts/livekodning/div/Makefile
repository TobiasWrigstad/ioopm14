CC=gcc
FLAGS=-Wall -ggdb -std=c99
PROGRAMS=div divArray divPointer divStructHeap divStructStack

$(PROGRAMS):%: %.c tuple.o
	$(CC) $(FLAGS) -o $@ $< tuple.o

tuple.o: tuple.c tuple.h
	$(CC) $(FLAGS) -c $<

clean: 
	rm -f $(PROGRAMS) tuple.o
	rm -rf *.dSYM