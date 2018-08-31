#ifndef NUMERO

#define NUMERO
#include <iostream>
#include <math.h>

class numero{
private:
	double gene;
public:
	numero(double x=0):gene(x){}
	numero transa (numero n){
		numero filho((gene+n.gene)/2);
		filho.mutacao(20000,0);
		return filho;
	}
	void mutacao(int amnt =0, int prob = 0){
		double mut=rand()%amnt;
//		std::cout<<mut<<'\n';
		gene+=mut/100 - amnt/200;
	}
	double avalia(){
		return gene*(100-gene);
	}
	void set(double x){
		gene=x;
	}
	void debug(){
		std::cout<<gene<<std::endl;
	}
	double get_gene(){
		return gene;
	}
};

#endif
