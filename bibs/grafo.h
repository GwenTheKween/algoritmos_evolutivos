#ifndef GRAFO_HEADER

#define GRAFO_HEADER
#include "mapa.h"
#include <stdio.h>
#include <math.h>
#include <vector>
#include <stack>
#include <set>

class grafo{
private:
    map m;
    std::vector<coord> doors; //important coordinates contain keys, to open the doors
    std::vector<coord> keys;
    std::set<coord> doors_and_keys;//all cdoors and keys toghether, so that no tile can be chosen twice
public:
    grafo(){}; //sanity 
    //Initiates the graph with a given height and width. if only one parameter is given, starts a square graph
    grafo(int,int = -1);
    //graph destructor
    ~grafo();

    //get important coordinates
    std::vector<coord> get_keys(){return keys;}
    std::vector<coord> get_doors(){return doors;}

    //operator overloads
    tile& operator [](coord P){return m[P];}

    //Generates a new map, based on a given paramter, if passed. if nothing is passed, generates a new map
    void gen_map();
    void generate_loops(int = 5);
    void draw(); //parte do aulos, usando ncurses.
    void debug();

    //calculates the minimun distance between 2 points
    std::vector<coord> BFS(coord,coord);
    std::vector<coord> BFS(int,int,int,int);
    void unlock(coord);
};


#endif
