JAVAFILES=$(shell ls model/*.java) $(shell ls view/*.java) $(shell ls controller/*.java)
CLASSFILES=$(JAVAFILES:.java=.class)

all: $(CLASSFILES)

$(CLASSFILES): %.class: %.java
	javac $<

run: all
	./run

clean:
	rm -rf $(CLASSFILES) model/*.class view/*.class controller/*.class

.PHONY: all run clean
