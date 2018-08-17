#ifndef EVOLUTIVO
#define EVOLUTIVO
#include <iostream>
#include <vector>
#include "numero.h"

enum tipos_de_transa{
	ELITISMO,
	CASINHAS,
	TORNEIO,
};

template<class type> class evolutivo{
private:
	std::vector<type> individuo;
	std::vector<double> notas;
public:
	evolutivo(){}; //presente por motivos de debug
	evolutivo(std::vector<type>);
	~evolutivo(){};
	void itera(int = 1,int = ELITISMO); //faz n iteracoes
	type get_best();
	std::vector<type> get_all_individuo(){return individuo;};
	std::vector<type> transa_por_elitismo();
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

template<class type>void evolutivo<type>::itera(int n,int tipo_transa){
	/*comeca apenas com elitismo*/
	for(int gen=0;gen<n;gen++){
		if(tipo_transa==ELITISMO)
			individuo=transa_por_elitismo();
		for(int i=0;i<individuo.size();i++)
			notas[i]=individuo[i].avalia();
	}
}

template<class type> std::vector<type> evolutivo<type>::transa_por_elitismo(){
	//calcula qual eh o melhor individuo
	int best=0;
	std::vector<numero> nova_geracao;
	for(int i=1;i<notas.size();i++){
		if(notas[best]<notas[i]) best=i;
	}
	//faz ele transar com todo mundo e avalia os filhos
	for(int i=0;i<individuo.size();i++){
		if(i!=best){
			nova_geracao.push_back(individuo[i].transa(individuo[best]));
		}else{
			nova_geracao.push_back(individuo[i]);
		}
	}
	return nova_geracao;
}

#endif
