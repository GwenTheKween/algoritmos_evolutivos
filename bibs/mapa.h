#ifndef MAPA_HEADER

#define MAPA_HEADER

#include "tile.h"

class map{
private:
    tile** t;
    int height, width;
public:
    map(int h,int w=-1):
        height(h),
        width((w>0)?w:h)
    {
        t=new tile*[height];
        t[0]=new tile[height*width];
        for(int i=1;i<height;i++){
            t[i]=t[i-1]+height;
        }
    }
    ~map(){
        delete[] t[0];
        delete[] t;
    }
    void add_direction(char dir, coord c){
        t[c.x][c.y]^=dir;
        if(dir==UP) t[c.x-1][c.y]^=DOWN;
        else if(dir == DOWN) t[c.x+1][c.y]^=UP;
        else if(dir == LEFT) t[c.x][c.y-1]^=RIGHT;
        else if(dir == RIGHT) t[c.x][c.y+1]^=LEFT;
    }
};

#endif
