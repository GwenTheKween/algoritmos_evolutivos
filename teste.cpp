#include "bibs/evo.h"
#include <stdlib.h>

int main(){
	std::vector<numero> init;
	numero n;
	for(int i=0;i<5;i++){
		n.set(rand()%200);
		n.debug();
		init.push_back(n);
	}
	evolutivo<numero> e(init);
	e.itera(20);
	n=e.get_best();
	n.debug();
	return 0;
}
