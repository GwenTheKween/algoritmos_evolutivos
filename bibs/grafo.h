#ifndef GRAFO_LIB

#define GRAFO_LIB
#include <stdio.h>
#include <math.h>
#include <vector>
#include <stack>

//directions and their respective bits
enum{
    UP = 1,
    DOWN = 2,
    LEFT = 4,
    RIGHT = 8
};

//class to represent a coordinate
class coord{
public:
    int x,y;
};

class grafo{
private:
    char** map;
    int width,height;
    std::vector<coord> imp; //important coordinates contain keys, to open the doors
public:
    grafo(){}; //sanity check
    //Initiates the graph with a given height and width. if only one parameter is given, starts a square graph
    grafo(int,int = -1);
    //graph destructor
    ~grafo();
    //Generates a new map, based on a given paramter, if passed. if nothing is passed, generates a new map
    void gen_map(char** = NULL);
    void draw(); //parte do aulos, usando ncurses.
    void debug();
};


#endif
