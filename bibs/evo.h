#include <iostream>
#include <vector>

template<class type> class individuo{
protected:
	std::vector<type> genes;
public:
	//expandir as transas para os multiplos jeitos possiveis
	virtual void transa(individuo*) = 0; //transa com uma pessoa soh
	virtual void transa(std::vector<individuo>) = 0; //suruba com n pessoas
	//range da mutacao e probabilidade que um gene sofra mutacao. se <=0, 1 gene eh escolhido aleatoriamente
	virtual void mutacao(int, int = 0) = 0;
	virtual double avalia() = 0;
	std::vector<type> get_genes(){return genes;};
};

template<class type> class evolutivo{
private:
	std::vector<individuo<type> > ind;
	std::vector<double> notas;
public:
	evolutivo(){}; //presente por motivos de debug
	evolutivo(std::vector<individuo<type> >);
	~evolutivo(){};
	void itera(int = 1); //faz n iteracoes
	double get_best();
};
