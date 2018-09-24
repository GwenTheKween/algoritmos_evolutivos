#ifndef GRAFO_LIB

#define GRAFO_LIB
#include <stdio.h>
#include <math.h>
#include <queue>
#include <vector>

enum{
    UP = 1,
    DOWN = 2,
    LEFT = 4,
    RIGHT = 8
};

class coord{
public:
    int x,y;
};

class grafo{
private:
    char** map;
    int width,height;
    std::vector<coord> imp; //which are the important coordinates
public:
    grafo(){}; //sanity check
    grafo(int,int = -1);
    ~grafo();
    void gen_map(char** = NULL);
    void draw(); //parte do aulos, usando ncurses.
    void debug();
};


#endif
