#include "mapa.h"
#include "robot.h"

class runner: public robo{
private:
	map m;
public:
	runner(map& model):robo(model),m(model){}
	runner(runner const&);
	runner(runner&&);

	runner& operator = (runner const&);
	runner& operator = (runner&&);

	int avalia();
	runner transa(runner&,int);
	void animate();
};
