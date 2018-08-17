COMP = g++
COMPFLAGS = -O3 -std=c++11 -g
LINKFLAGS = -o
NOME = test
CFILES = teste.cpp
BIBS = $(wildcard bibs/*.h)

all: test

test: $(CFILES) $(BIBS)
	$(COMP) $(CFILES) $(COMPFLAGS) $(LINKFLAGS) $(NOME)

run: test
	./$(NOME)

clear:
	rm $(OFILES) $(NOME)


aa:
	echo $(CFILES)
