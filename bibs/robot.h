#ifndef ROBOTSdotTXT
#define ROBOTSdotTXT

#include "mapa.h"
#include <unistd.h>
#include <iostream>

class robo{
private:
    std::vector<coord> gene;
    std::vector<coord> path;
    table t;
public:
    robo(const robo&);
    robo(map&);
    ~robo(){}

	std::vector<coord> get_gene(){return gene;}
	std::vector<coord> get_path(){return path;}
	table get_t(){return t;}

	void set_gene(std::vector<coord> g){gene = g;}
	void set_path(std::vector<coord> p){path = p;}
	void set_table_entry(int entry,int new_val){t.set_entry(entry,new_val);}

    void simulate(map&);
    int avalia(map&);
    void debug();
    int decision(int);

    void random();
    robo transa(robo&,int);
    void mutacao();
    void animate(map&,std::vector<coord>&);

    void save(std::ofstream&);
    void read(std::ifstream&);
};

#endif
