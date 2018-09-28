#ifndef MAPA_HEADER

#define MAPA_HEADER

#include "tile.h"
#include <queue>

class map{
private:
    tile** t;
    int height, width;
public:
    map(int h=0,int w=-1):
        height(h),
        width((w>0)?w:h)
    {
        t=new tile*[height];
        t[0]=new tile[height*width];
        for(int i=1;i<width;i++){
            t[i]=t[i-1]+height;
        }
    }
    ~map(){
        delete[] t[0];
        delete[] t;
    }

    int h(){return height;}
    int w(){return width;}

    tile& operator [](coord P){ return t[P.x()][P.y()];}

    bool can_move(coord pos,int dir){
        return  ((dir == UP) && pos.x() > 0)        ||
                ((dir ==DOWN)&& pos.x() < height -1)||
                ((dir ==LEFT)&& pos.y() > 0)        ||
                ((dir==RIGHT)&& pos.y() < width - 1);
    }

    void connect(char dir, coord c){
        t[c.x()][c.y()].add_dir(dir);
        c=c.move(dir);
        t[c.x()][c.y()].add_dir((dir<=DOWN)?(dir^(DOWN|UP)):(dir^(LEFT|RIGHT)));
    }

    int BFS(coord p1,coord p2){
        std::queue<coord> q;
        coord inc_dist; //when to increment the distance
        int len=0; //current distance

        //which positions are unvisited so far
        char unv[height][width];
        q.push(p1);

        for(int i=0;i<height;i++)
            for(int j=0;j<width;j++) unv[i][j]=1;

        //chooses the first new direction that the algorithm will follow as the next coordinate to increment distance
        if(((*this)[p1]).up()) inc_dist=p1.move(UP);
        else if(((*this)[p1]).down()) inc_dist = p1.move(DOWN);
        else if(((*this)[p1]).left()) inc_dist = p1.move(LEFT);
        else if(((*this)[p1]).right())inc_dist = p1.move(RIGHT);

        while(!q.empty()){
            p1=q.front();
            q.pop();
            unv[p1.x()][p1.y()]=0;

            //we reached a new level on the BFS tree, increase the distance and calculates when the new level will be reached
            if(p1==inc_dist){
                len++;
                if((((*this)[p1]).up())&& unv[p1.x()-1][p1.y()]) inc_dist=p1.move(UP);
                else if((((*this)[p1]).down())&& unv[p1.x()+1][p1.y()]) inc_dist = p1.move(DOWN);
                else if((((*this)[p1]).left())&& unv[p1.x()][p1.y()-1]) inc_dist = p1.move(LEFT);
                else if((((*this)[p1]).right())&& unv[p1.x()][p1.y()+1])inc_dist = p1.move(RIGHT);
            }

            //if the FINAL DESTINATION was reached, return the distance
            if(p1==p2) return len;

            //adds all possible directions to the queue
            if(((*this)[p1].up())&& unv[p1.x()-1][p1.y()]) q.push(p1.move(UP));
            if(((*this)[p1].down())&& unv[p1.x()+1][p1.y()]) q.push(p1.move(DOWN));
            if(((*this)[p1].left())&& unv[p1.x()][p1.y()-1]) q.push(p1.move(LEFT));
            if(((*this)[p1].right())&& unv[p1.x()][p1.y()+1]) q.push(p1.move(RIGHT));

        }

        //no path could be found
        return -1;
    }
};

#endif
