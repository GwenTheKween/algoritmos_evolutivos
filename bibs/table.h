#include "coord.h"
#include <stdlib.h>
#include <vector>

#define TABLESIZE 0x4000 

enum actions{
	MOVE_UP = 1,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	ACTION_SIZE = 4
};

enum direction{
	NORTH = 0x03,
	SOUTH = 0x0c,
	 EAST = 0x30,
	 WEST = 0xc0
};

enum visible{ 
	//to be used as (CONNECTED & NORTH) | (BIFURCATION & SOUTH)
	BIFURCATION = 0xaa,
	CONNECTED = 0x55,
	//to be used as relative_dir << MINOTAUR | relative_dir << KEY_DIR
	MINOTAUR = 8,
	KEY_DIR = 11
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

	void save(std::ofstream&);
	void read(std::ifstream&);
};
