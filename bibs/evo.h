#include <iostream>
#include <vector>

class numero{
private:
	double gene;
public:
	numero(double x=0):gene(x){}
	numero transa (numero n){
		numero filho((gene+n.gene)/2);
		filho.mutacao(0,0);
		return filho;
	}
	void mutacao(int amnt =0, int prob = 0){
		gene+=((double)(rand()%300))/100 - 1;
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
};

template<class type> class evolutivo{
private:
	std::vector<type> individuo;
	std::vector<double> notas;
public:
	evolutivo(){}; //presente por motivos de debug
	evolutivo(std::vector<type>);
	~evolutivo(){};
	void itera(int = 1); //faz n iteracoes
	double get_best();
};
