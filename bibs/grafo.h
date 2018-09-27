#ifndef GRAFO_LIB

#define GRAFO_LIB
#include "tile.h"
#include <stdio.h>
#include <math.h>
#include <vector>
#include <stack>
#include <queue>

class grafo{
private:
    map m;
    int width,height;
    std::vector<coord> doors; //important coordinates contain keys, to open the doors
    std::vector<coord> keys;
public:
    grafo(){}; //sanity check
    //Initiates the graph with a given height and width. if only one parameter is given, starts a square graph
    grafo(int,int = -1);
    //graph destructor
    ~grafo();

    //get important coordinates
    std::vector<coord> get_important(){return imp;}

    //operator overloads
    char& operator [](coord P){return map[P.x][P.y];}

    //Generates a new map, based on a given paramter, if passed. if nothing is passed, generates a new map
    void gen_map(tile** = NULL);
    void draw(); //parte do aulos, usando ncurses.
    void debug();

    //calculates the minimun distance between 2 points
    int BFS(coord,coord);
    int BFS(int,int,int,int);
};


#endif
