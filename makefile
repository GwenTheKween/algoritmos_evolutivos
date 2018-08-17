COMP = g++
COMPFLAGS = -O3 -std=c++11 -c -g
LINKFLAGS = -o
NOME = test
CFILES = $(wildcard bibs/*.cpp) teste.cpp
OFILES = $(CFILES:.cpp=.o)

all: test

test: $(OFILES)
	$(COMP) $(OFILES) $(LINKFLAGS) $(NOME)

bibs/%.o:bibs/%.cpp bibs/%.h
	$(COMP) $< $(COMPFLAGS) -o $@

teste.o:teste.cpp
	$(COMP) $< $(COMPFLAGS) -o $@

run: test
	./$(NOME)

clear:
	rm $(OFILES) $(NOME)


aa:
	echo $(CFILES)
