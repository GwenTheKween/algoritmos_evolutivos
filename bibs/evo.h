#include <iostream>
#include <vector>

template <class type>
class individuo{
protected:
	std::vector<type> genes;
public:
	//expandir as transas para os multiplos jeitos possiveis
	virtual individuo transa(individuo); //transa com uma pessoa soh
	virtual individuo transa(std::vector<individuo>); //suruba com n pessoas
	//range da mutacao e probabilidade que um gene sofra mutacao. se <=0, 1 gene eh escolhido aleatoriamente
	virtual void mutacao(int, int = 0);
	virtual double avalia();
};

class evolutivo{
private:
	std::vector<individuo> ind;
	std::vector<double> notas;
public:
	evolutivo(){}; //presente por motivos de debug
	evolutivo(std::vector<individuo>);
	~evolutivo();
	void itera(int = 1); //faz n iteracoes
	double get_best();
};
