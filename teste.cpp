#include "bibs/evo.h"

class numero : private individuo<double>{
public:
	numero(double x=0){
		genes.push_back(x);
	}
	numero transa (numero n){
		numero filho=(genes[0]+n.genes[0])/2;
		filho.mutacao(0,0);
		return filho;
	}
	void mutacao(int amnt =0, int prob = 0){
		genes[0]+=((double)(rand()%300))/100 - 1;
	}
	double avalia(){
		return genes[0]*(100-genes[0]);
	}
};

int main(){
	std::vector<numero> init;
	return 0;
}
