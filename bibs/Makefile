COMP=g++
CFILES=$(wildcard *.cpp)
HFILES=$(wildcard *.h)
OFILES=$(CFILES:.cpp=.o)
FINAL=prog
LINKFLAGS = -lm -o
COMPFLAGS = -c -g -std=c++11 -Wall -pedantic

all: $(FINAL)

$(FINAL): $(OFILES) $(HFILES)
	$(COMP) $(OFILES) $(LINKFLAGS) $(FINAL)

%.o:%.cpp %.h
	$(COMP) $< $(COMPFLAGS) -o $@

%.o:%.cpp
	$(COMP) $< $(COMPFLAGS) -o $@


run: $(FINAL)
	./$(FINAL)

test:
	echo $(OFILES) $(FINAL)
clear:
	rm $(OFILES) $(FINAL)
