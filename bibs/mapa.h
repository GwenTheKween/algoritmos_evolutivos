#ifndef MAPA_HEADER

#define MAPA_HEADER

#include "tile.h"
#include "table.h"
#include <queue>
#include <algorithm>
#include <vector>
#include <stack>

class map{
private:
    int height, width;
	std::vector<std::vector<tile> > t;
	std::vector<coord> doors;
	std::vector<coord> keys;
	coord initMinotaur,Minotaur;
public:
	//constructors, all of them!!
    map(int h=0,int w=-1):height(h),width((w>0)?w:h),t(height,std::vector<tile>(width)),doors(0),keys(0){}
    map(const map& m); //copy constructor
    map(map&& m); //move constructor
    map(map& model);
	//destructor
    ~map(){
		for(unsigned int i=0;i<t.size();i++) t[i].clear();
		t.clear();
    }

	//get parameters from the object
    int h(){return height;}
    int w(){return width;}
	std::vector<coord> get_keys(){return keys;}
	std::vector<coord> get_doors(){return keys;}
	coord get_Minotaur(){return Minotaur;}

	//operator overrides
    tile operator [](coord P)const {return t[P.x()][P.y()];}
    map& operator =(const map& other); //copy operator
    map& operator = (map&& m);//move operator


    bool can_move(coord,int);
    void connect(char, coord);
    int look_around(coord);
    coord updateMinotaur(coord);
    void resetMinotaur(){Minotaur = initMinotaur;}

    //return the smallest path from p1 to p2 EXCLUDING P1
    std::vector<coord> BFS(coord p1,coord p2);
	std::vector<coord> BFS(int p1x,int p1y, int p2x, int p2y);
	//lock door again, after it's been open
    void lock(coord);
	//open door
    void unlock(coord);
	//lock all doors again
	void reset();
	//generate a map, by running a DFS, generating loops and adding doors
	void gen_map(int);
	void generate_loops(int);
	void DFS(coord);
	//pretty draw of the map
	void draw() {animate(coord(-1,-1),coord(-1,-1));}
	void animate(coord,coord);

	void save(std::ofstream&);
	void read(std::ifstream&);
};

#endif
