#ifndef NUMERO

#define NUMERO
#include <iostream>
#include <math.h>


//test class, to ensure that the evolutivo class is, indeed, finding a maximum
class numero{
private:
	double gene;
public:
	numero(double x=0):gene(x){} //class constructor, sets the gene to be the given number
    //cross-over method, receives another number to cross-over with, and how much it's children should mutate
        //the mutation range has to be passed as a parameter so that variable mutation range can be correctly implemented
	numero transa (numero n,int range_mut){
		numero filho((gene+n.gene)/2);
		filho.mutacao(range_mut);
		return filho;
	}
    //mutation method, mutates the babies by up to 0.005*range up or down
	void mutacao(int range =0){
		double mut=rand()%range;
		gene+=mut/100 - range/200;
	}
    //method for evaluating the fitness of the individual, in this case a simple function
	double avalia(){
		return gene*(1000-gene)+1000*sin(0.75*gene);
	}
    //sets the value of the gene, useful for debugging
	void set(double x){
		gene=x;
	}
    //simple debug method
	void debug(char c='\n'){
		std::cout<<gene<<c;
	}
    //returns the gene, TBA usability with some verbose features
	double get_gene(){
		return gene;
	}
	void random(){
		gene = rand()%2000;
	}
};

#endif
