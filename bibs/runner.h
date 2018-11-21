#include "mapa.h"
#include "robot.h"

class runner: public robo{
private:
	map m;
	coord position;
	int keys_acquired;
public:
	runner(map& model):robo(model),m(model),position(0,0),keys_acquired(0){}
	runner(runner const&);
	runner(runner&&);

	runner& operator = (runner const&);
	runner& operator = (runner&&);

	int avalia();
	runner transa(runner&,int);
	void mutacao(int);
	void animate();
};
