#include "mapa.h"

map::map(const map& m):
	height(m.height),
	width(m.width),
	t(m.t),
	doors( m.doors),
	keys(m.keys)
	{}

map::map(map&& m):
	height(m.height),
	width(m.width),
	t(m.t),
	doors(m.doors),
	keys(m.keys)
	{}

map::map(map& model):
	height(model.h()),
	width(model.w()),
	t(model.t),
	doors(model.doors),
	keys(model.keys)
	{}



map& map::operator =(const map& other){
	if(this != &other){
		t = other.t;
		height = other.height;
		width = other.width;
		keys = other.keys;
		doors = other.doors;
	}
	return (*this);
}

map& map::operator =(map&& m){
	if(this != &m){
		t=m.t;
		height=m.height;
		width=m.width;
	}
	return (*this);
}


bool map::can_move(coord pos, int dir){
	return  ((dir == UP) && pos.x() > 0)        ||
			((dir ==DOWN)&& pos.x() < height -1)||
			((dir ==LEFT)&& pos.y() > 0)        ||
			((dir==RIGHT)&& pos.y() < width - 1);
}

void map::connect(char dir, coord c){
	t[c.x()][c.y()].add_dir(dir);
	c=c.move(dir);
	t[c.x()][c.y()].add_dir((dir<=DOWN)?(dir^(DOWN|UP)):(dir^(LEFT|RIGHT)));
}

int map::look_around(coord pos){
	int i,ret=0;
	coord looking(pos);
	tile curr = (*this)[looking];
	//checks all the directions
	//first: up
	while(curr.connected(UP)){
		ret|=(//if current tile has a sideways conection
			(curr.connected(LEFT) || curr.connected(RIGHT))
			//then you can move up to find a bifurcation
			&(BIFURCATION & NORTH));
		looking = looking.move(UP);
		curr = (*this)[looking];
	}
	looking = pos;
	curr = (*this)[looking];
	//second: down
	while(curr.connected(DOWN)){
		ret|=(//if current tile has a sideways conection
			(curr.connected(LEFT) || curr.connected(RIGHT))
			//then you can move down to find a bifurcation
			&(BIFURCATION & SOUTH));
		looking = looking.move(DOWN);
		curr = (*this)[looking];
	}
	looking = pos;
	curr = (*this)[looking];
	//third: left
	while(curr.connected(LEFT)){
		ret|=(//if current tile has a vertical conection
			(curr.connected(UP) || curr.connected(DOWN))
			//then you can move left to find a bifurcation
			&(BIFURCATION & EAST));
		looking = looking.move(LEFT);
		curr = (*this)[looking];
	}
	looking = pos;
	curr = (*this)[looking];
	//last: right
	while(curr.connected(RIGHT)){
		ret|=(//if current tile has an vertical conection
			(curr.connected(UP) || curr.connected(DOWN))
			//then you can move right to find a bifurcation
			&(BIFURCATION & WEST));
		looking = looking.move(RIGHT);
		curr=(*this)[looking];
	}
	return ret;
}

std::vector<coord> map::BFS(coord p1,coord p2){
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

std::vector<coord> map::BFS(int p1x, int p1y, int p2x, int p2y){
	return BFS(coord(p1x,p1y),coord(p2x,p2y));
}

void map::lock(coord pos){
	int dir = (*this)[pos].get_lock_dir();
	if((*this)[pos].connected(dir)){
		(*this)[pos].unlock();
		(*this)[pos.move(dir)].add_dir(dir^((dir<LEFT)?(DOWN|UP):(LEFT|RIGHT)));
	}
}

void map::unlock(coord key){
	unsigned int dir,i;
	coord door;
	for(i=0; i<keys.size();i++){
		if(key == keys[i]){
			door = doors[i];
			break;
		}
	}
	if(i==keys.size()) return; //invalid key
	dir=(*this)[door].get_lock_dir();
	(*this)[door].unlock();
	(*this)[door.move(dir)].add_dir(dir^((dir<LEFT)?(DOWN|UP):(LEFT|RIGHT)));
}

void map::reset(){
	for(unsigned int i=0;i<doors.size();i++){
		lock(doors[i]);
	}
}

void map::gen_map(int n){
	coord pos(rand() % height, rand() % width);
	DFS(pos);
	generate_loops(n);
}

void map::generate_loops(int n){
	coord door(rand()%h(),rand()%w()),key(rand()%h(),rand()%w());
	std::vector<int> dirs;
	bool already_chosen;
	int new_dir;
	for(int i=0;i<n;i++){
		door.set(rand()%h(),rand()%w());

		already_chosen = false;
		for(unsigned int j=0;j<doors.size() && !already_chosen;j++){
			already_chosen = (door == doors[j]) || (door == keys[j]);
		}
		if(already_chosen){
			i--;
			continue;
		}

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
			//door.set(rand()%h(), rand()%w());
			continue;
		}

		key.set(rand()%h(),rand()%w());

		already_chosen = false;
		for(unsigned int j=0;j<doors.size() && !already_chosen;j++){
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
		t[door.x()][door.y()].lock(new_dir);

		doors.push_back(door);
		keys.push_back(key);

		dirs.clear();
	}
}

void map::DFS(coord pos){
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

void map::animate(coord pos){
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
			for(unsigned int k=0;k<keys.size() && b==0;k++)   b=(p==keys[k]);
			for(unsigned int k=0;k<doors.size() && b==0 ;k++){
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
