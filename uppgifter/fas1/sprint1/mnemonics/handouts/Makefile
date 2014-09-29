all:	remember

# Java settings
JAVA_COMPILER   = javac
JAVA_OPTIONS    = -d build 

# C settings
C_COMPILER   = gcc
C_OPTIONS    = -Wall -O4 

# Clean settings
GEN_EXTENSIONS = build/remember/*.class


numgen:	numgen.c
	$(C_COMPILER) $(C_OPTIONS) -o numgen numgen.c

builddir:
	mkdir -p build

remember: builddir build/remember/Dictionary.class build/remember/FileUtils.class build/remember/Mnemonics.class build/remember/Numbers.class

clean:
	rm -f $(GEN_EXTENSIONS)

build/remember/Dictionary.class: remember/Dictionary.java
	$(JAVA_COMPILER) $(JAVA_OPTIONS) $<

build/remember/FileUtils.class: remember/FileUtils.java
	$(JAVA_COMPILER) $(JAVA_OPTIONS) $<

build/remember/Mnemonics.class: remember/Mnemonics.java
	$(JAVA_COMPILER) $(JAVA_OPTIONS) $<

build/remember/Numbers.class: remember/Numbers.java
	$(JAVA_COMPILER) $(JAVA_OPTIONS) $<

run: remember
	java -cp build remember.Mnemonics
