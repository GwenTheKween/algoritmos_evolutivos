#include "evo.h"

template<class type> evolutivo<type>::evolutivo(std::vector<type> v):
	individuo(v), //inicializa o vetor de individuos com os individuos passados
	notas(v.size(),0) //inicializa um vetor com v.size() zeros
	{
	int i;
	for(i=0;i<v.size();i++){
		notas[i]=v[i].avalia();
	}
}

template<class type>double evolutivo<type>::get_best(){
	double best=notas[0];
	for(int i=1;i<notas.size();i++){
		if(best<notas[i]) best=notas[i];
	}
	return best;
}

template<class type>void evolutivo<type>::itera(int n){
	/*comeca apenas com elitismo*/
	int best;
	for(int gen=0;gen<n;gen++){
		best=0;
		for(int i=1;i<notas.size();i++){
			if(notas[best]<notas[i]) best=i;
		}
		for(int i=0;i<individuo.size();i++){
			individuo[i].transa(individuo[best]);
			notas[i]=individuo[i].avalia();
		}
	}
}
