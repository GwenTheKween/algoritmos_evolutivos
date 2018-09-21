#ifndef NUMERO

#define NUMERO
#include <iostream>
#include <math.h>

class numero{
private:
	double gene;
public:
	numero(double x=0):gene(x){}
	numero transa (numero n,int range_mut){
		numero filho((gene+n.gene)/2);
		filho.mutacao(range_mut);
		return filho;
	}
	void mutacao(int range =0){
		double mut=rand()%range;
//		std::cout<<mut<<'\n';
		gene+=mut/100 - range/200;
	}
	double avalia(){
		return gene*(1000-gene)+1000*sin(0.75*gene);
	}
	void set(double x){
		gene=x;
	}
	void debug(char c='\n'){
		std::cout<<gene<<c;
	}
	double get_gene(){
		return gene;
	}
};

#endif
