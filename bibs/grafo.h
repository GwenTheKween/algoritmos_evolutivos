#ifndef GRAFO_LIB

#define GRAFO_LIB
#include <stdio.h>
#include <math.h>
#include <vector>
#include <stack>
#include <queue>

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
    coord(int a=0,int b=0):x(a),y(b){} // constructor, receives up to 2 numbers as the coordinates.

    bool operator ==(coord other){
        return ((x==other.x) && (y==other.y));
    }

    //directions from the current coordinate
    coord up(){
        coord c(x-1,y);
        return c;
    }
    coord down(){
        coord c(x+1,y);
        return c;
    }
    coord left(){
        coord c(x,y-1);
        return c;
    }
    coord right(){
        coord c(x,y+1);
        return c;
    }
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

    //get important coordinates
    std::vector<coord> get_important(){return imp;}

    //operator overloads
    char& operator [](coord P){return map[P.x][P.y];}

    //Generates a new map, based on a given paramter, if passed. if nothing is passed, generates a new map
    void gen_map(char** = NULL);
    void draw(); //parte do aulos, usando ncurses.
    void debug();

    //calculates the minimun distance between 2 points
    int BFS(coord,coord);
    int BFS(int,int,int,int);
};


#endif
