#ifndef COORD_HEADER

#define COORD_HEADER

#include <iostream>

//directions and their respective bits
enum{
    UP = 1,
    DOWN = 2,
    LEFT = 4,
    RIGHT = 8
};

const int direction[] = {UP, DOWN, LEFT, RIGHT};
const int dir_size = 4;

//class to represent a coordinate
class coord{
private:
    int X,Y;
public:
    coord(int a=0,int b=0):X(a),Y(b){} // constructor, receives up to 2 numbers as the coordinates.

    void set(int a,int b){
        X=a;
        Y=b;
    }
    int x(){return X;}
    int y(){return Y;}

    bool operator ==(coord other){
        return ((X==other.X) && (Y==other.Y));
    }

    //returns the coordinate after the desired movement
    coord move(int dir){
        if(dir == UP) return coord(X-1,Y);
        else if(dir == DOWN) return coord(X+1,Y);
        else if(dir == LEFT) return coord(X,Y-1);
        else if(dir == RIGHT) return coord(X,Y+1);
    }

};

#endif
