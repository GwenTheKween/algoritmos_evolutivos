#include "grafo.h"

//=====================================================================================================================================================
//Internal functions used only for map generation

//Random DFS to generate a tree as the map. This is only the first step of the map generation
void DFS(map m,coord pos){
    std::vector<int> unv;
    std::stack<coord> path;
    int dir;
    path.push(pos);
    //while there's still a path to follow
    while(!path.empty()){
        //takes the last position of the path
        pos=path.top();

        //add to the vector all unvisited directions from the current position
        for(int i=0;i<dir_size;i++){
            if(m.can_move(pos,direction[i]) && //if you can move to that direction
               m[pos.move(direction[i])].unconnected())//and the tile in that direction is not connected to anything
            {
                unv.push_back(direction[i]);
            }
        }

        //if there are unvisited neighbours, choose one randomly and adds them as the last position of the path
        if(unv.size()>0){
            dir=rand()%unv.size();
            dir=unv[dir];
            //the direction is added by xor-ing the position and the direction, because each position is a bitmap of the possible directions
            m.connect(dir,pos);
            path.push(pos);
            path.push(pos.move(dir));
        }else //if no more paths can be followed from the current position, backtracks to the last position;
            path.pop();
        //clears the unvisited neighbours vector
        unv.clear();
    }
}

//Chooses a few random positions to turn into doors
void generate_loops(map m,int n=5){ //n indicates how many doors, and thus loops, are to be generated
    coord door,key;
    std::vector<int> dirs;
    int new_dir;
    for(int i=0;i<n;i++){
        door.set(rand()%m.h(), rand()%m.w());

        //directions that have no connection and represent a possible movement
        for(int j=0;j<dir_size;j++){
            if((!(m[door].connected(direction[j]))) && m.can_move(door,direction[j])) dirs.push_back(direction[j]);
        }

        if(dirs.size()==0){ //no possible directions to open
            i--;
            continue;
        }

        //chooses a new direction to connect
        new_dir=rand()%dirs.size();
        new_dir=dirs[new_dir];

        key.set(rand() % m.h(), rand() % m.w());
//        mat[pos.x][pos.y]^=new_dir; //adds the direction

        //adds the possibility to move back
//        if(new_dir==UP)     mat[pos.x-1][pos.y]^=DOWN;
//        else if(new_dir==DOWN)   mat[pos.x+1][pos.y]^=UP;
//        else if(new_dir==LEFT)   mat[pos.x][pos.y-1]^=RIGHT;
//        else if(new_dir==RIGHT)  mat[pos.x][pos.y+1]^=LEFT;

        dirs.clear();
    }
}

//=====================================================================================================================================================
grafo::grafo(int h, int w):m(h,w){}

grafo::~grafo(){
    m.~map();
}

void grafo::gen_map(){
    //if a model map was passed, copies it into the graph
    coord pos(rand() % m.h(),rand() % m.w());
    DFS(m,pos);
    generate_loops(m);
}

void grafo::draw(){
    //prints the map using a 3x3 space, very ugly, just for debug sake
    coord p;
    for(int i=0;i<m.h();i++){
        for(int j=0;j<m.w();j++){
            p.set(i,j);
            printf(" %c ",(m[p].up())?' ':'.');
        }
        printf("\n");
        for(int j=0;j<m.w();j++){
            p.set(i,j);
            printf("%c.%c",(m[p].left())?' ':'.',(m[p].right())?' ':'.');
        }
        printf("|\n");
        for(int j=0;j<m.w();j++){
            p.set(i,j);
            printf(" %c ",(m[p].down())?' ':'.');
        }
        printf("\n");
    }
    return;
}

void grafo::debug(){ //prints the map as a  bitmap of directions, pretty tough to read, but good for debugging
    tile t;
    coord p;
    for(int i=0;i<m.h();i++){
        for(int j=0;j<m.w();j++){
            p.set(i,j);
            t=m[p];
            printf("%d%d%d%d\t",t.right(),t.left(),t.down(),t.up());
        }
        printf("\n");
    }
    return;
}

//method for finding the smallest path between coordinates p1 and p2
int grafo::BFS(coord p1, coord p2){
    return m.BFS(p1,p2);
}

int grafo::BFS(int p1x,int p1y,int p2x, int p2y){
    coord p1(p1x,p1y),p2(p2x,p2y);
    return m.BFS(p1,p2);
}
