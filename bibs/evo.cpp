#include "evo.h"

template <class type> evolutivo<type>::evolutivo(std::vector<type> v):
	ind(v), //inicializa o vetor de individuos com os individuos passados
	notas(v.size(),0) //inicializa um vetor com v.size() zeros
	{
	int i;
	for(i=0;i<v.size();i++){
		notas[i]=v[i].avalia();
	}
};

template <class type> double evolutivo<type>::get_best(){
	double best=notas[0];
	for(int i=1;i<notas.size();i++){
		if(best<notas[i]) best=notas[i];
	}
	return best;
}
