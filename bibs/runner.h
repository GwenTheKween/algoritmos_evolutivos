#include "mapa.h"
#include "robot.h"

class runner: public robo{
private:
	map m;
	coord position;
	int keys_acquired;
	std::vector<coord> mino_path;
public:
	runner(map& model):robo(model),m(model),position(0,0),keys_acquired(0),mino_path(){}
	runner(runner const&);
	runner(runner&&);

	runner& operator = (runner const&);
	runner& operator = (runner&&);

	int avalia();
	runner transa(runner&,int);
	void mutacao(int);
	void animate();
};
