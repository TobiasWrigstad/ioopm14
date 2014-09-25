all: test

# Tex settings
C_COMPILER   = gcc
C_OPTIONS    = -ggdb -Wall -std=c99

# Clean settings
GEN_EXTENSIONS = *.o *.out

# SCM
VC_PROGRAM = git

clean:
	rm -f $(GEN_EXTENSIONS) unittests *.orig

commit: beautify clean test
	$(VC_PROGRAM) pull; $(VC_PROGRAM) commit; $(VC_PROGRAM) push

%:	%.c
	$(C_COMPILER) $(C_OPTIONS) $< -o $@

beautify:
	astyle -A7 *.c *.h

test: unittests.c istring.c istring.h
	$(C_COMPILER) $(C_OPTIONS) unittests.c istring.c -o unittests -lcunit
	./unittests

