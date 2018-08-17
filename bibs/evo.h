#ifndef EVOLUTIVO
#define EVOLUTIVO
#include <iostream>
#include <vector>
#include "numero.h"

template<class type> class evolutivo{
private:
	std::vector<type> individuo;
	std::vector<double> notas;
public:
	evolutivo(){}; //presente por motivos de debug
	evolutivo(std::vector<type>);
	~evolutivo(){};
	void itera(int = 1); //faz n iteracoes
	type get_best();
};

template<class type> evolutivo<type>::evolutivo(std::vector<type> v):
	individuo(v), //inicializa o vetor de individuos com os individuos passados
	notas(v.size(),0) //inicializa um vetor com v.size() zeros
	{
	int i;
	for(i=0;i<v.size();i++){
		notas[i]=v[i].avalia();
	}
}

template<class type>type evolutivo<type>::get_best(){
	double best=0;
	for(int i=1;i<notas.size();i++){
		if(notas[best]<notas[i]) best=i;
	}
	return individuo[best];
}

template<class type>void evolutivo<type>::itera(int n){
	/*comeca apenas com elitismo*/
	int best;
	for(int gen=0;gen<n;gen++){
		printf("geracao: %d\n",gen);
		//calcula qual eh o melhor individuo
		best=0;
		for(int i=1;i<notas.size();i++){
			if(notas[best]<notas[i]) best=i;
		}
		//faz ele transar com todo mundo e avalia os filhos
		for(int i=0;i<individuo.size();i++){
			if(i!=best){
				individuo[i]=individuo[i].transa(individuo[best]);
				notas[i]=individuo[i].avalia();
			}
			printf("individuo %d:  (%lf,%lf)\n",i,individuo[i].get_gene(),notas[i]);
		}
		printf("\n\n");
	}
}


#endif
