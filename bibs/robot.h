#ifndef ROBOTSdotTXT
#define ROBOTSdotTXT

#include "grafo.h"

class robo{
private:
    grafo g;
    std::vector<coord> gene;
    std::vector<coord> path;
public:
    robo(grafo&);
    ~robo(){
        g.~grafo();
    }

    void simulate();
    int avalia();
    void debug();

    void mutacao(grafo&);
};

#endif
