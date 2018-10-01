#include "grafo.h"

//=====================================================================================================================================================
//Internal functions used only for map generation

//Random DFS to generate a tree as the map. This is only the first step of the map generation
void DFS(map& m,coord pos){
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
            path.push(pos.move(dir));
        }else //if no more paths can be followed from the current position, backtracks to the last position;
            path.pop();
        //clears the unvisited neighbours vector
        unv.clear();
    }
}


//=====================================================================================================================================================
grafo::grafo(int h, int w):m(h,w){}

grafo::grafo(grafo& model):
    m(model.m),
    doors(model.doors),
    keys(model.keys),
    doors_and_keys(model.doors_and_keys)
    {}

grafo::~grafo(){
    m.~map();
}

grafo& grafo::operator =(const grafo& other){
    m=other.m;
    keys=other.keys;
    doors=other.doors;
    doors_and_keys=other.doors_and_keys;
}

void grafo::gen_map(int n){
    //if a model map was passed, copies it into the graph
    coord pos(rand() % m.h(),rand() % m.w());
    DFS(m,pos);
    generate_loops(n);
}

//Chooses a few random positions to turn into doors
void grafo::generate_loops(int n){ //n indicates how many doors, and thus loops, are to be generated
    coord door(rand()%m.h(),rand()%m.w()),key(rand()%m.h(),rand()%m.w());
    std::vector<int> dirs;
    std::set<coord>::iterator end = doors_and_keys.end();
    int new_dir;
    for(int i=0;i<n;i++){
        while(doors_and_keys.find(door) != end) 
            door.set(rand()%m.h(), rand()%m.w());

        //directions that have no connection and represent a possible movement
        for(int j=0;j<dir_size;j++){
            if((!(m[door].connected(direction[j]))) && 
                  m.can_move(door,direction[j]) && 
                  (m[door.move(direction[j])].get_lock_dir() != (direction[j]^((direction[j]<LEFT)?(UP|DOWN):(LEFT|RIGHT))))) 
                    dirs.push_back(direction[j]);
        }

        if(dirs.size()==0){ //no possible directions to open
            i--;
            //a new door has to be chosen, otherwise this turns into an infinite loop
            door.set(rand()%m.h(), rand()%m.w());
            continue;
        }

        //chooses a new direction to connect and turns the tile into a door
        new_dir=rand()%dirs.size();
        new_dir=dirs[new_dir];
        m[door].lock(new_dir);

        //if this tile can be turned into a door, add it to the set before choosing the key
        //to make sure that they dont end up in the same place
        doors_and_keys.insert(door);
        while(doors_and_keys.find(key)!=end)
            key.set(rand() % m.h(), rand() % m.w());
        doors.push_back(door);
        keys.push_back(key);
        doors_and_keys.insert(key);
//        mat[pos.x][pos.y]^=new_dir; //adds the direction

        //adds the possibility to move back
//        if(new_dir==UP)     mat[pos.x-1][pos.y]^=DOWN;
//        else if(new_dir==DOWN)   mat[pos.x+1][pos.y]^=UP;
//        else if(new_dir==LEFT)   mat[pos.x][pos.y-1]^=RIGHT;
//        else if(new_dir==RIGHT)  mat[pos.x][pos.y+1]^=LEFT;

        dirs.clear();
    }
}

void grafo::draw(){
    //prints the map using a 3x3 space, very ugly, just for debug sake
    coord p;
    char body[]={'.','*','^','v','<','>'};
    int b;
    for(int i=0;i<m.h();i++){
        for(int j=0;j<m.w();j++){
            p.set(i,j);
            printf(" %c ",(m[p].up())?'.':' ');
        }
        printf("\n");
        for(int j=0;j<m.w();j++){
            p.set(i,j);
            b=0;
            for(int k=0;k<keys.size() && b==0;k++)   b=(p==keys[k]);
            for(int k=0;k<doors.size() && b==0 ;k++){
                if(p==doors[k]){
                    int lock_dir=m[p].get_lock_dir();
                    b=2*(lock_dir==UP)+3*(lock_dir==DOWN)+4*(lock_dir==LEFT)+5*(lock_dir==RIGHT);
                }
            }
            printf("%c%c%c",(m[p].left())?'.':' ',body[b],(m[p].right())?'.':' ');
        }
        printf("\n");
        for(int j=0;j<m.w();j++){
            p.set(i,j);
            printf(" %c ",(m[p].down())?'.':' ');
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
            t.debug('\t');
            //printf("%d%d%d%d\t",t.right(),t.left(),t.down(),t.up());
        }
        printf("\n");
    }
    return;
}

//method for finding the smallest path between coordinates p1 and p2
std::vector<coord> grafo::BFS(coord p1, coord p2){
    return m.BFS(p1,p2);
}

std::vector<coord> grafo::BFS(int p1x,int p1y,int p2x, int p2y){
    coord p1(p1x,p1y),p2(p2x,p2y);
    return m.BFS(p1,p2);
}

void grafo::unlock(coord key){
    coord door;
    int i;
    for(i=0;i<keys.size();i++){
        if(keys[i]==key){
            door=doors[i];
            break;
        }
    }
    if(i==keys.size()) return; //invali key

    //unlocks the door
    m.unlock(door);

    //removes this door and key from the graph
    doors_and_keys.erase(door);
    doors_and_keys.erase(key);
    keys.erase(keys.begin()+i);
    doors.erase(doors.begin()+i);
}
