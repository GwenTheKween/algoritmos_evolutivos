#include "coord.h"
#include <stdlib.h>
#include <vector>

#define TABLESIZE 0x10000

enum actions{
	MOVE_UP = 1,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	ACTION_SIZE = 4
};

enum direction{
	NORTH = 0x000f,
	SOUTH = 0x00f0,
	 EAST = 0x0f00,
	 WEST = 0xf000
};

enum visible{ 
	//to be used as (MINOTAUR & NORTH) | (BIFURCATION & SOUTH)
	MINOTAUR = 0x8888,
	BIFURCATION = 0x2222,
	KEY_DIR = 0x4444,
	CONNECTED = 0x1111
};

class table{
private:
	char reaction[TABLESIZE];
public:
	table(){}
	table(const table&);
	table(table&&);

	void gen_random();
	table cross_over(table&);
	void debug();
	void set_entry(int entry,int new_val){reaction[entry] = new_val;}

	table operator = (const table& other);
	table operator = (table&& other);
	char operator[] (int val) const {return reaction[val];}
};
