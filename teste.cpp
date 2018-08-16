#include "bibs/evo.h"
#include <stdlib.h>

class numero : public individuo{
private:
	std::vector<double> genes;
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
	void set(double x){
		genes[0]=x;
	}
	void debug(){
		std::cout<<genes[0]<<std::endl;
	}
};

int main(){
	std::vector<individuo> init;
	numero n;
	for(int i=0;i<5;i++){
		n.set(rand()%200);
		n.debug();
		init.push_back(n);
	}
	evolutivo e(init);
	e.itera(20);
	n=e.get_best();
	n.debug();
	return 0;
}
