#include "grafo.h"

//=====================================================================================================================================================
void DFS(char*** mat,coord pos,int h,int w){
    std::vector<int> unv;
    int dir;
    while(1){
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
        if(unv.size()>0){
            dir=rand()%unv.size();
            dir=unv[dir];
            (*mat)[pos.x][pos.y]^=dir;
            if(dir==UP){
                pos.x--;
                (*mat)[pos.x][pos.y]=DOWN;
                DFS(mat,pos,h,w);
                pos.x++;
            }else if(dir==DOWN){
                pos.x++;
                (*mat)[pos.x][pos.y]=UP;
                DFS(mat,pos,h,w);
                pos.x--;
            }else if(dir==LEFT){
                pos.y--;
                (*mat)[pos.x][pos.y]=RIGHT;
                DFS(mat,pos,h,w);
                pos.y++;
            }else{
                pos.y++;
                (*mat)[pos.x][pos.y]=LEFT;
                DFS(mat,pos,h,w);
                pos.y--;
            }
        }else break;
        unv.clear();
    }
}

//=====================================================================================================================================================
grafo::grafo(int w, int h):
    width(w),
    height((h>0)?h:w)
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
    if(model){
        int i,j;
        for(i=0;i<height;i++){
            for(j=0;j<width;j++){
                map[i][j]=model[i][j];
            }
        }
    }else{
        coord pos;
        pos.x=pos.y=0;
        DFS(&map,pos,height,width);
    }
}

void grafo::draw(){
    return;
}

void grafo::debug(){
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

