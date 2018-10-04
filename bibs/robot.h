#ifndef ROBOTSdotTXT
#define ROBOTSdotTXT

#include "grafo.h"

class robo{
private:
    grafo g;
    std::vector<coord> gene;
    std::vector<coord> path;
public:
    robo(robo&);
    robo(grafo&);
    ~robo(){}

    void simulate();
    int avalia();
    void debug();

    robo transa(robo&,grafo&);
    void mutacao(grafo&);
};

#endif
