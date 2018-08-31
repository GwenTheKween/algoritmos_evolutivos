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
	./$(NOME) -t e -v > $(DATA_FILE)e
	./$(NOME) -t t -v > $(DATA_FILE)t
	./plot.py 0-2 $(DATA_FILE)e $(DATA_FILE)t

clear:
	rm $(OFILES) $(NOME)


aa:
	echo $(CFILES)
