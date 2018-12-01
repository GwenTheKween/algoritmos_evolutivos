#ifndef TILE_HEADER

#define TILE_HEADER

#include "coord.h"

class tile{
private:
    char dir;
    char lock_dir;
public:
    tile():dir(0),lock_dir(0){}

    void add_dir(char direc){
        dir^=direc;
    }
    void unlock(){
        dir^=lock_dir;
    }
    void lock(int direc){
        lock_dir = direc;
    }

    char get_lock_dir(){return lock_dir;}

    void debug(char c='\n'){
        printf("%d%c",dir,c);
    }

    bool unconnected(){
        return dir==0;
    }
    bool connected(int direc){
        return dir&direc;
    }

    void save(std::ofstream& f){
	    int val = lock_dir;
	    val = (val << 8) + dir;
	    f << val;
	    f << '\t';
    }

    void read(std::ifstream& f){
	    int val;
	    f >> val;
	    dir = val&255;
	    lock_dir = val >> 8;
    }
};

#endif
