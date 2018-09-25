#include "grafo.h"

//=====================================================================================================================================================
//Random DFS to generate a tree as the map. This is only the first step of the map generation
void DFS(char*** mat,coord pos,int h,int w){
    std::vector<int> unv;
    std::stack<coord> path;
    int dir;
    path.push(pos);
    //while there's still a path to follow
    while(!path.empty()){
        //takes the last position of the path
        pos=path.top();

        //check which of the neighbours are not visited by 
        if(pos.x > 0 && ((*mat)[pos.x-1][pos.y]==0)){
            unv.push_back(UP);
        }
        if(pos.x+1 < h && ((*mat)[pos.x+1][pos.y]==0)){
            unv.push_back(DOWN);
        }
        if(pos.y > 0 && ((*mat)[pos.x][pos.y-1]==0)){
            unv.push_back(LEFT);
        }
        if(pos.y+1 < w && ((*mat)[pos.x][pos.y+1]==0)){
            unv.push_back(RIGHT);
        }

        //if there are unvisited neighbours, choose one randomly and adds them as the last position of the path
        if(unv.size()>0){
            dir=rand()%unv.size();
            dir=unv[dir];
            //the direction is added by xor-ing the position and the direction, because each position is a bitmap of the possible directions
            (*mat)[pos.x][pos.y]^=dir;
            if(dir==UP){
                pos.x--;
                (*mat)[pos.x][pos.y]=DOWN;
                path.push(pos);
            }else if(dir==DOWN){
                pos.x++;
                (*mat)[pos.x][pos.y]=UP;
                path.push(pos);
            }else if(dir==LEFT){
                pos.y--;
                (*mat)[pos.x][pos.y]=RIGHT;
                path.push(pos);
            }else{
                pos.y++;
                (*mat)[pos.x][pos.y]=LEFT;
                path.push(pos);
            }
        }else //if no more paths can be followed from the current position, backtracks to the last position;
            path.pop();
        //clears the unvisited neighbours vector
        unv.clear();
    }
}

//=====================================================================================================================================================
grafo::grafo(int w, int h):
    width(w),
    height((h>0)?h:w)//if a desired height was given, use that, otherwise makes a square matrix
    {
    map=new char*[height];
    map[0]=new char[width*height];
    for(int i=1;i<height;i++){
        map[i]=map[i-1]+height;
    }
}

grafo::~grafo(){
    delete[] map[0];
    delete[] map;
}

void grafo::gen_map(char** model){
    //if a model map was passed, copies it into the graph
    if(model){
        int i,j;
        for(i=0;i<height;i++){
            for(j=0;j<width;j++){
                map[i][j]=model[i][j];
            }
        }
    }else{ //otherwise chooses randomly a start position and generates a map
        coord pos;
        pos.x=rand()%height;
        pos.y=rand()%width;
        DFS(&map,pos,height,width);
        //Generate_loops(&map,height,width);
    }
}

void grafo::draw(){
    //so far does nothing, but at some point will print the map using ncurses
    return;
}

void grafo::debug(){ //prints the map as a  bitmap of directions, pretty tough to read, but good for debugging
    int t;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            t=map[i][j];
            printf("%d%d%d%d\t",(t&RIGHT)>>3,(t&LEFT)>>2,(t&DOWN)>>1,t&UP);
        }
        printf("\n");
    }
    return;
}


