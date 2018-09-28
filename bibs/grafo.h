#ifndef GRAFO_HEADER

#define GRAFO_HEADER
#include "mapa.h"
#include <stdio.h>
#include <math.h>
#include <vector>
#include <stack>

class grafo{
private:
    map m;
    std::vector<coord> doors; //important coordinates contain keys, to open the doors
    std::vector<coord> keys;
public:
    grafo(){}; //sanity check
    //Initiates the graph with a given height and width. if only one parameter is given, starts a square graph
    grafo(int,int = -1);
    //graph destructor
    ~grafo();

    //get important coordinates
//    std::vector<coord> get_important(){return imp;}

    //operator overloads
    tile& operator [](coord P){return m[P];}

    //Generates a new map, based on a given paramter, if passed. if nothing is passed, generates a new map
    void gen_map();
    void generate_loops(int = 5);
    void draw(); //parte do aulos, usando ncurses.
    void debug();

    //calculates the minimun distance between 2 points
    int BFS(coord,coord);
    int BFS(int,int,int,int);
};


#endif
