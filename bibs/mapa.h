#ifndef MAPA_HEADER

#define MAPA_HEADER

#include "tile.h"
#include <queue>
#include <algorithm>
#include <vector>
#include <stack>

class map{
private:
    tile** t;
    int height, width;
	std::vector<coord> doors;
	std::vector<coord> keys;
public:
    map(int h=0,int w=-1):
        height(h),
        width((w>0)?w:h)
    {
        t=new tile*[height];
        t[0]=new tile[height*width];
	for(int i=1;i<height;i++){
            t[i]=t[i-1]+width;
        }
    }
    map(const map& m){ //copy constructor
        coord c;
        height = m.height;
        width = m.width;
        t=new tile*[height];
        t[0] = new tile[height*width];
        for(int i=1;i<height;i++) t[i]=t[i-1]+width;
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                t[i][j]=m.t[i][j];
            }
        }
		doors = m.doors;
		keys = m.keys;
    }
    map(map&& m){ //move constructor
        height = m.height;
        width = m.width;
        delete[] t[0];
        delete[] t;
        t=m.t;
		doors = m.doors;
		keys = m.keys;
    }
    map(map& model):
        height(model.h()),
        width(model.w())
    {
        int i,j;
        t=new tile*[height];
        t[0]=new tile[height*width];
        for(j=0;j<width;j++) t[0][j]=model.t[0][j];
        for(i=1;i<height;i++){
            t[i]=t[i-1]+width;
            for(j=0;j<width;j++) t[i][j]=model.t[i][j];
        }
		doors = model.doors;
		keys = model.keys;
    }
    ~map(){
        delete[] t[0];
        delete[] t;
    }

    int h(){return height;}
    int w(){return width;}
	std::vector<coord> get_keys(){return keys;}
	std::vector<coord> get_doors(){return keys;}

    tile& operator [](coord P)const { return t[P.x()][P.y()];}

    map& operator =(const map& other){
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				t[i][j]=other.t[i][j];
			}
		}
		keys = other.keys;
		doors = other.doors;
    }
    map& operator = (map&& m) noexcept{
        if(this != &m){
            delete[] t[0];
            delete[] t;
            t=m.t;
            height=m.height;
            width=m.width;
        }
    }

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

	std::vector<coord> BFS(int p1x,int p1y, int p2x, int p2y){
		coord p1(p1x,p1y), p2(p2x,p2y);
		return BFS(p1,p2);
	}

    //return the smallest path from p1 to p2 EXCLUDING P1
    std::vector<coord> BFS(coord p1,coord p2){
        std::queue<coord> q;
        std::vector<coord> path;
        //matriz indicating which was the coordinate prior to his one
        coord parent[height][width];
        coord unvisited(-1,-1);

        q.push(p1);

        for(int i=0;i<height;i++)
            for(int j=0;j<width;j++) parent[i][j].set(-1,-1);
        //coordinate -1,-1 indicates that this tile was not visited yet

        //sets the first tile to be it's own parent as the end condition
        parent[p1.x()][p1.y()]=p1; 

        while(!q.empty()){
            p1=q.front();
            q.pop();

            //if the FINAL DESTINATION was reached, exit the loop
            if(p1==p2) break;

            //adds all possible directions to the queue
            if(((*this)[p1].up())&& parent[p1.x()-1][p1.y()]==unvisited){
                q.push(p1.move(UP));
                parent[p1.x()-1][p1.y()]=p1;
            }
            if(((*this)[p1].down())&& parent[p1.x()+1][p1.y()]==unvisited){
                q.push(p1.move(DOWN));
                parent[p1.x()+1][p1.y()]=p1;
            }
            if(((*this)[p1].left())&& parent[p1.x()][p1.y()-1]==unvisited){
                q.push(p1.move(LEFT));
                parent[p1.x()][p1.y()-1]=p1;
            }
            if(((*this)[p1].right())&& parent[p1.x()][p1.y()+1]==unvisited){
                q.push(p1.move(RIGHT));
                parent[p1.x()][p1.y()+1]=p1;
            }

        }
        if(parent[p2.x()][p2.y()]==unvisited) return path;//empty because no path could be found
        path.push_back(p2);
        p1=parent[p2.x()][p2.y()];
        while(p1!=parent[p1.x()][p1.y()]){
            path.push_back(p1);
            p1=parent[p1.x()][p1.y()];
        }
        //path is reversed, must change it back
        std::reverse(path.begin(),path.end());
        return path;
    }

    void lock(coord pos){
        int dir = (*this)[pos].get_lock_dir();
        if((*this)[pos].connected(dir)){
            (*this)[pos].unlock();
            (*this)[pos.move(dir)].add_dir(dir^((dir<LEFT)?(DOWN|UP):(LEFT|RIGHT)));
        }
    }

    void unlock(coord key){
        int dir,i;
		coord door;
		for(i=0; i<keys.size();i++){
			if(key == keys[i]){
				door = doors[i];
				break;
			}
		}
		if(i==keys.size()) return; //invalid key
        dir=(*this)[key].get_lock_dir();
        (*this)[key].unlock();
        (*this)[key.move(dir)].add_dir(dir^((dir<LEFT)?(DOWN|UP):(LEFT|RIGHT)));
    }
	
	void reset(){
		for(int i=0;i<doors.size();i++){
			lock(doors[i]);
		}
	}

	void gen_map(int n){
		coord pos(rand() % height, rand() % width);
		DFS(pos);
		generate_loops(n);
	}

	void generate_loops(int n){
		coord door(rand()%h(),rand()%w()),key(rand()%h(),rand()%w());
		std::vector<int> dirs;
		bool already_chosen;
		int new_dir;
		for(int i=0;i<n;i++){
			door.set(rand()%h(),rand()%w());

			already_chosen = false;
			for(int j=0;j<doors.size() && !already_chosen;j++){
				already_chosen = (door == doors[j]) || (door == keys[j]);
			}
			if(already_chosen){
				i--;
				continue;
			}
	//        while(doors_and_keys.find(door) != end) 
	//            door.set(rand()%m.h(), rand()%m.w());

			//directions that have no connection and represent a possible movement
			for(int j=0;j<dir_size;j++){
				if((!((*this)[door].connected(direction[j]))) && 
					  can_move(door,direction[j]) && 
					  ((*this)[door.move(direction[j])].get_lock_dir() != (direction[j]^((direction[j]<LEFT)?(UP|DOWN):(LEFT|RIGHT))))) 
						dirs.push_back(direction[j]);
			}

			if(dirs.size()==0){ //no possible directions to open
				i--;
				//a new door has to be chosen, otherwise this turns into an infinite loop
				door.set(rand()%h(), rand()%w());
				continue;
			}

			//if this tile can be turned into a door, add it to the set before choosing the key
			//to make sure that they dont end up in the same place
	//        doors_and_keys.insert(door);

			key.set(rand()%h(),rand()%w());

			already_chosen = false;
			for(int j=0;j<doors.size() && !already_chosen;j++){
				already_chosen = (key == doors[j]) || (key == keys[j]);
			}
			if(already_chosen){
				i--;
				continue; 
			}
			//only lock if the key could be chosen

			//chooses a new direction to connect and turns the tile into a door
			new_dir=rand()%dirs.size();
			new_dir=dirs[new_dir];
			lock(new_dir);

			doors.push_back(door);
			keys.push_back(key);
	//        doors_and_keys.insert(key);
	//        mat[pos.x][pos.y]^=new_dir; //adds the direction
			//adds the possibility to move back
	//        if(new_dir==UP)     mat[pos.x-1][pos.y]^=DOWN;
	//        else if(new_dir==DOWN)   mat[pos.x+1][pos.y]^=UP;
	//        else if(new_dir==LEFT)   mat[pos.x][pos.y-1]^=RIGHT;
	//        else if(new_dir==RIGHT)  mat[pos.x][pos.y+1]^=LEFT;

			dirs.clear();
		}
	}

	void DFS(coord pos){
		std::vector<int> unv;
		std::stack<coord> path;
		int dir;
		path.push(pos);
		//while there is still a path to follow
		while(!path.empty()){
			//takes the last position of the path
			pos=path.top();

			//add to the vector all unvisited directions from the current position
			for(int i=0;i<dir_size;i++){
				if(can_move(pos,direction[i]) && //if you can move to that direction
				   (*this)[pos.move(direction[i])].unconnected())//and the tile in that direction is not connected to anything
				{
					unv.push_back(direction[i]);
				}
			}

			//if there are unvisited neighbours, choose one randomly and adds them as the last position of the path
			if(unv.size()>0){
				dir=rand()%unv.size();
				dir=unv[dir];
				//the direction is added by xor-ing the position and the direction, because each position is a bitmap of the possible directions
				connect(dir,pos);
				path.push(pos.move(dir));
			}else //if no more paths can be followed from the current position, backtracks to the last position;
				path.pop();
			//clears the unvisited neighbours vector
			unv.clear();

		}
	}

	void draw(){
		//prints the map using a 3x3 space, very ugly, just for debug sake
		coord p;
		char body[]={'.','*','^','v','<','>'};
		int b;
		for(int i=0;i<h();i++){
			for(int j=0;j<w();j++){
				p.set(i,j);
				printf(" %c ",((*this)[p].up())?'.':' ');
			}
			printf("\n");
			for(int j=0;j<w();j++){
				p.set(i,j);
				b=0;
				for(int k=0;k<keys.size() && b==0;k++)   b=(p==keys[k]);
				for(int k=0;k<doors.size() && b==0 ;k++){
					if(p==doors[k]){
						int lock_dir=(*this)[p].get_lock_dir();
						b=2*(lock_dir==UP)+3*(lock_dir==DOWN)+4*(lock_dir==LEFT)+5*(lock_dir==RIGHT);
					}
				}
				printf("%c%c%c",((*this)[p].left())?'.':' ',body[b],((*this)[p].right())?'.':' ');
			}
			printf("\n");
			for(int j=0;j<w();j++){
				p.set(i,j);
				printf(" %c ",((*this)[p].down())?'.':' ');
			}
			printf("\n");
		}
		return;
	}

	void animate(coord pos){
		//prints the map using a 3x3 space, very ugly, just for debug sake
		coord p;
		char body[]={'.','*','^','v','<','>','@'};
		int b;
		for(int i=0;i<h();i++){
			for(int j=0;j<w();j++){
				p.set(i,j);
				printf(" %c ",((*this)[p].up())?'.':' ');
			}
			printf("\n");
			for(int j=0;j<w();j++){
				p.set(i,j);
				b=0;
				for(int k=0;k<keys.size() && b==0;k++)   b=(p==keys[k]);
				for(int k=0;k<doors.size() && b==0 ;k++){
					if(p==doors[k]){
						int lock_dir=(*this)[p].get_lock_dir();
						b=2*(lock_dir==UP)+3*(lock_dir==DOWN)+4*(lock_dir==LEFT)+5*(lock_dir==RIGHT);
					}
				}
				if(p==pos) b=6;
				printf("%c%c%c",((*this)[p].left())?'.':' ',body[b],((*this)[p].right())?'.':' ');
			}
			printf("\n");
			for(int j=0;j<w();j++){
				p.set(i,j);
				printf(" %c ",((*this)[p].down())?'.':' ');
			}
			printf("\n");
		}
		return;
	}
};

#endif
