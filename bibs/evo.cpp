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
