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
	//constructors, all of them!!
    map(int =0,int =-1);
    map(const map& m); //copy constructor
    map(map&& m); //move constructor
    map(map& model);
	//destructor
    ~map(){
        delete[] t[0];
        delete[] t;
    }

	//get parameters from the object
    int h(){return height;}
    int w(){return width;}
	std::vector<coord> get_keys(){return keys;}
	std::vector<coord> get_doors(){return keys;}

	//operator overrides
    tile& operator [](coord P)const { return t[P.x()][P.y()];}
    map& operator =(const map& other); //copy operator
    map& operator = (map&& m);//move operator


    bool can_move(coord,int);
    void connect(char, coord);

    //return the smallest path from p1 to p2 EXCLUDING P1
    std::vector<coord> BFS(coord p1,coord p2);
	std::vector<coord> BFS(int p1x,int p1y, int p2x, int p2y);

    void lock(coord);

    void unlock(coord);
	
	void reset();

	void gen_map(int);

	void generate_loops(int);

	void DFS(coord);

	void draw(){
		animate(coord(-1,-1));
	}

	void animate(coord);
};

#endif
