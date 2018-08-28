#include "bibs/evo.h"

int main(){
	std::vector<numero> init;
	numero n;
	for(int i=0;i<5;i++){
		n.set(rand()%2000 - 500); //vai de -50 a 150, com o maximo sendo exatamente no meio
		init.push_back(n);
	}
	evolutivo<numero> e(init,ELITISMO);
	e.itera(20,true);
	n=e.get_best();
	return 0;
}
