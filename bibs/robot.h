#ifndef ROBOTSdotTXT
#define ROBOTSdotTXT

#include "grafo.h"

class robo{
private:
    grafo g;
    std::vector<coord> gene;
    std::vector<coord> path;
public:
    robo(const robo&);
    robo(grafo&);
    ~robo(){}

    void simulate();
    int avalia();
    void debug();

    robo transa(robo&,int);
    void mutacao();
    void animate();
};

#endif
