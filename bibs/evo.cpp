#include "evo.h"

evolutivo::evolutivo(std::vector<individuo> v):
	ind(v), //inicializa o vetor de individuos com os individuos passados
	notas(v.size(),0) //inicializa um vetor com v.size() zeros
	{
	int i;
	for(i=0;i<v.size();i++){
		notas[i]=v[i].avalia();
	}
}

double evolutivo::get_best(){
	double best=notas[0];
	for(int i=1;i<notas.size();i++){
		if(best<notas[i]) best=notas[i];
	}
	return best;
}

void evolutivo::itera(int n){
	/*comeca apenas com elitismo*/
	int best;
	for(int gen=0;gen<n;gen++){
		best=0;
		for(int i=1;i<notas.size();i++){
			if(notas[best]<notas[i]) best=i;
		}
		for(int i=0;i<ind.size();i++){
			ind[i].transa(ind[best]);
			notas[i]=ind[i].avalia();
		}
	}
}
