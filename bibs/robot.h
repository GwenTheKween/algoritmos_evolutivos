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

	std::vector<coord> get_gene(){return gene;}
	std::vector<coord> get_path(){return path;}

	void set_gene(std::vector<coord> g){gene = g;}
	void set_path(std::vector<coord> p){path = p;}

    void simulate(map&);
    int avalia(map&);
    void debug();

    void random();
    robo transa(robo&,int);
    void mutacao();
    void animate(map&);
};

#endif
