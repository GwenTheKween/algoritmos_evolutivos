#include "bibs/evo.h"
#include <stdlib.h>

class numero : public individuo<double>{
public:
	numero(double x=0){
		genes.push_back(x);
	}
	void transa (individuo* n) override {
		double filho=(genes[0]+n->get_genes()[0])/2;
		genes[0]=filho;
		mutacao(0,0);
	}
	void transa (std::vector<individuo> n) override{}
	void mutacao(int amnt =0, int prob = 0) override {
		genes[0]+=((double)(rand()%300))/100 - 1;
	}
	double avalia() override {
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
	std::vector<individuo<double> > init;
	numero n;
	for(int i=0;i<5;i++){
		n.set(rand()%200);
		n.debug();
		init.push_back(n);
	}
	evolutivo<double> e(init);
	e.itera(20);
	n=e.get_best();
	n.debug();
	return 0;
}
