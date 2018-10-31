#ifndef ROBOTSdotTXT
#define ROBOTSdotTXT

#include "mapa.h"
#include <unistd.h>
#include <iostream>

class robo{
private:
    std::vector<coord> gene;
    std::vector<coord> path;
public:
    robo(const robo&);
    robo(map&);
    ~robo(){}

    void simulate(map&);
    int avalia(map&);
    void debug();

    robo transa(robo&,int);
    void mutacao();
    void animate();
};

#endif
