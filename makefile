COMP = g++
COMPFLAGS = -O3 -std=c++11 -g
LINKFLAGS = -o
NOME = test
CFILES = teste.cpp
BIBS = $(wildcard bibs/*.h)
DATA_FILE = dados

all: test

test: $(CFILES) $(BIBS)
	$(COMP) $(CFILES) $(COMPFLAGS) $(LINKFLAGS) $(NOME)

run: test
	./$(NOME) > $(DATA_FILE) 

clear:
	rm $(OFILES) $(NOME)


aa:
	echo $(CFILES)
