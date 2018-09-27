#include "grafo.h"

//=====================================================================================================================================================
//Internal functions used only for map generation

//Random DFS to generate a tree as the map. This is only the first step of the map generation
void DFS(char **mat,coord pos,int h, int w){
    std::vector<int> unv;
    std::stack<coord> path;
    int dir;
    path.push(pos);
    //while there's still a path to follow
    while(!path.empty()){
        //takes the last position of the path
        pos=path.top();

        //check which of the neighbours are not visited by 
        if(pos.x > 0 && (mat[pos.x-1][pos.y]==0)){
            unv.push_back(UP);
        }
        if(pos.x+1 < h && (mat[pos.x+1][pos.y]==0)){
            unv.push_back(DOWN);
        }
        if(pos.y > 0 && (mat[pos.x][pos.y-1]==0)){
            unv.push_back(LEFT);
        }
        if(pos.y+1 < w && (mat[pos.x][pos.y+1]==0)){
            unv.push_back(RIGHT);
        }

        //if there are unvisited neighbours, choose one randomly and adds them as the last position of the path
        if(unv.size()>0){
            dir=rand()%unv.size();
            dir=unv[dir];
            //the direction is added by xor-ing the position and the direction, because each position is a bitmap of the possible directions
            mat[pos.x][pos.y]^=dir;
            if(dir==UP){
                pos.x--;
                mat[pos.x][pos.y]=DOWN;
                path.push(pos);
            }else if(dir==DOWN){
                pos.x++;
                mat[pos.x][pos.y]=UP;
                path.push(pos);
            }else if(dir==LEFT){
                pos.y--;
                mat[pos.x][pos.y]=RIGHT;
                path.push(pos);
            }else{
                pos.y++;
                mat[pos.x][pos.y]=LEFT;
                path.push(pos);
            }
        }else //if no more paths can be followed from the current position, backtracks to the last position;
            path.pop();
        //clears the unvisited neighbours vector
        unv.clear();
    }
}

//Chooses a few random positions to turn into loops
void generate_loops(char **mat, int h, int w,int n=5){ //n indicates how many new connections should be generated
    coord pos;
    std::vector<int> dirs;
    int new_dir;
    for(int i=0;i<n;i++){
        pos.x=rand()%h;
        pos.y=rand()%w;

        //directions that have no connection and represent a possible movement
        if(!(mat[pos.x][pos.y]&UP)      && pos.x > 0)dirs.push_back(UP);
        if(!(mat[pos.x][pos.y]&DOWN)    && pos.x+1 < h)dirs.push_back(DOWN);
        if(!(mat[pos.x][pos.y]&LEFT)    && pos.y > 0)dirs.push_back(LEFT);
        if(!(mat[pos.x][pos.y]&RIGHT)   && pos.y+1 < w)dirs.push_back(RIGHT);

        //chooses a new direction to connect
        new_dir=rand()%dirs.size();
        new_dir=dirs[new_dir];
        mat[pos.x][pos.y]^=new_dir; //adds the direction

        //adds the possibility to move back
        if(new_dir==UP)     mat[pos.x-1][pos.y]^=DOWN;
        else if(new_dir==DOWN)   mat[pos.x+1][pos.y]^=UP;
        else if(new_dir==LEFT)   mat[pos.x][pos.y-1]^=RIGHT;
        else if(new_dir==RIGHT)  mat[pos.x][pos.y+1]^=LEFT;

        dirs.clear();
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
        DFS(map,pos,height, width);
        generate_loops(map,height,width);
    }
}

void grafo::draw(){
    //prints the map using a 3x3 space, very ugly, just for debug sake
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            printf("|%c|",(map[i][j]&UP)?' ':'-');
        }
        printf("\n");
        for(int j=0;j<width;j++){
            printf("%c %c",(map[i][j]&LEFT)?' ':'|',(map[i][j]&RIGHT)?' ':'|');
        }
        printf("|\n");
        for(int j=0;j<width;j++){
            printf("|%c|",(map[i][j]&DOWN)?' ':'-');
        }
        printf("\n");
    }
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


