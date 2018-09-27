#ifndef TILE_HEADER

#define TILE_HEADER

#include <iostream>


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

class tile{
private:
    char dir;
    char lock_dir;
public:
    tile():dir(0),lock_dir(0){}

    void add_dir(char direc){
        dir^=direc;
    }
    void unlock(){
        dir^=lock_dir;
    }

    bool up(){ // if the tile is connected upwards
        return dir&UP;
    }
    bool down(){ // if the tile is connected downwards
        return dir&DOWN;
    }
    bool left(){ // if the tile is connected leftwards
        return dir&LEFT;
    }
    bool right(){ // if the tile is connected rightwards
        return dir&RIGHT;
    }
};

#endif
