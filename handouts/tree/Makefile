all:	ex

CFLAGS=-g -Wall -std=c11

tree.o:	
	gcc $(CFLAGS) -c tree/tree.c

node.o:	
	gcc $(CFLAGS) -c tree/node.c

util.o:	
	gcc $(CFLAGS) -c tree/util.c

balance.o:	
	gcc $(CFLAGS) -c tree/balance.c

example_use.o:
	gcc $(CFLAGS) -c example_use.c

ex: example_use.o tree.o node.o util.o balance.o
	gcc $(CFLAGS) -o ex example_use.o tree.o node.o util.o balance.o

test:	ex
	./ex

dox:
	doxygen tree.cfg

clean:
	rm -f tree.o node.o util.o balance.o example_use.o ex
