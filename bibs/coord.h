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

/*
int invert(int dir){
    if(dir<LEFT) return dir^(UP|DOWN);
    return dir^(RIGHT|LEFT);
}
*/

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
    bool operator !=(coord other){
        return !(*this==other);
    }
    bool operator <(const coord other)const{
        if(X==other.X)
            return Y<other.Y;
        return X<other.X;
    }

    //returns the coordinate after the desired movement
    coord move(int dir){
        if(dir == UP) return coord(X-1,Y);
        else if(dir == DOWN) return coord(X+1,Y);
        else if(dir == LEFT) return coord(X,Y-1);
        else if(dir == RIGHT) return coord(X,Y+1);
		return coord(-1,-1);
    }

    void debug(char c='\t'){
        std::cout<<'('<<X<<','<<Y<<')'<<c;
    }
};

#endif
