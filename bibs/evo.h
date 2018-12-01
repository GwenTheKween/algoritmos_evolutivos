#ifndef EVOLUTIVO
#define EVOLUTIVO
#include <vector>
#include <stdlib.h>


//What types of cross-over can be used, translated as integers
enum tipos_de_transa{
	ELITISMO = 1,
	ROLETA,
	TORNEIO,
};


//what stop conditions can be used
enum condicoes_de_parada{
    FIXED=1,
    STABLE
};

//class that handles the evolution of the individuals, defined in another 
template<class type> class evolutivo{
private:
	std::vector<type> individuo; //current generations of individuals
	std::vector<double> notas; //current evaluation of said individuals
	int tipo; // type of cross-over to be used
    int range; // range of mutation
    int end_cond;//which end condition was chosen
    int stable_count; //how many generations have the scores been stable for
    int nuclear_countdown = 10; //if no other individuals surpass the current best,
   				//the whole population is "nuked", that is, a new
				//population is generated (with the current best preserved) 
public:
	//funcoes para inicializacao
	evolutivo(){}; //presente por motivos de debug
	evolutivo(std::vector<type>,int = ELITISMO,int = FIXED,int = 100);
	~evolutivo(){};

	//funcoes para pegar parametros
	type get_best(); //pega o melhor individuo
	std::vector<type> get_all_individuo(){return individuo;}; //pega todos os individuos
	int get_tipo(){return tipo;}; //pega o tipo de transa

	//funcoes para iterar as geracoes
	void itera(int = 1,bool = false); //faz n iteracoes
	std::vector<type> transa_por_elitismo();
	std::vector<type> transa_por_roleta();
	std::vector<type> transa_por_torneio(int = 2);//torneio com n individuos
	void nuke(); //will wipe out the current population and generate a new one
};

template<class type> evolutivo<type>::evolutivo(std::vector<type> v,int tipo_transa,int cond_end, int mut_rng):
	individuo(v), //inicializa o vetor de individuos com os individuos passados
	notas(v.size(),0), //inicializa um vetor com v.size() zeros
	tipo(tipo_transa),
    range(mut_rng),
    end_cond(cond_end),
    stable_count(0)
	{
	unsigned int i;
	for(i=0;i<individuo.size();i++){
		notas[i]=individuo[i].avalia(); //calculates all the scores from the start.
	}
}

//returns the best fitted individuals
template<class type>type evolutivo<type>::get_best(){
	double best=0;
	for(unsigned int i=1;i<notas.size();i++){
		if(notas[best]<notas[i]) best=i;
	}
	return individuo[best];
}

//method for iterating various generations of the evolution
template<class type>void evolutivo<type>::itera(int n,bool verbose){
    int gen=0, rng = range;


    // The count down is set up in order to be proportional to the amount of generations
    // that will be ran through.
    // It is also set up in order to allow for stability-based evolution, as the 
    // population would be always nuked whenver things started to get stable.
	if(end_cond==FIXED && n>10){
		nuclear_countdown = n/10;
	}
	else{
		nuclear_countdown = n+1;
	}

    //      if it has iterated       or     it has been stable for
    //      through all generations         enough generations
	while((gen<n && end_cond==FIXED) || (stable_count<n && end_cond==STABLE)){
		double mx=notas[0],sum=notas[0],new_mx;
		for(unsigned int i=1;i<notas.size();i++){
		    if(mx<notas[i])mx=notas[i]; //finds the best evaluation of the generation
		    sum+=notas[i];
		}
		if(verbose){
            //prints the average evaluation and the best evaluation
			std::cout<<gen<<'\t'<<mx<<'\t'<<sum/notas.size()<<'\n';
		}
		if(tipo==ELITISMO)
			individuo=transa_por_elitismo();
		else if(tipo==ROLETA)
			individuo=transa_por_roleta();
		else if(tipo==TORNEIO)
			individuo=transa_por_torneio();
		//finds the new best evaluation. Should it be the same as last, the generations have stabilized.
		notas[0]=individuo[0].avalia();
		new_mx=notas[0];
		for(unsigned int i=1;i<individuo.size();i++){
			notas[i]=individuo[i].avalia();
            		if(new_mx<notas[i]) new_mx=notas[i];
        	}
       		if(new_mx == mx){
            		stable_count++;
			nuclear_countdown--;
			range = rng*stable_count;	//Mutation range increases trying to find another maximum.
        	}else{
            		stable_count=0;
			range = rng;
			nuclear_countdown = 10;
        	}
		if(nuclear_countdown <= 0){
			nuke();
		}
        	gen++;
	}
}
//Kills all the population, preserving only the best individual from that group.
//Tries to find new ways to solve the problem whenever things get too stable.
template<class type> void evolutivo<type>::nuke(){
	int  i;
	individuo[0] = get_best();
	for(i=1;i<individuo.size();i++){
		individuo[i].random();
	}


	return;
}
template<class type> std::vector<type> evolutivo<type>::transa_por_elitismo(){
	//calcula qual eh o melhor individuo
	unsigned int best=0;
	std::vector<type> nova_geracao;
	for(unsigned int i=1;i<notas.size();i++){
		if(notas[best]<notas[i]) best=i;
	}
	//faz ele transar com todo mundo e avalia os filhos
	for(unsigned int i=0;i<individuo.size();i++){
		if(i!=best){
			nova_geracao.push_back(individuo[i].transa(individuo[best],range*stable_count));
		}else{
			nova_geracao.push_back(individuo[i]);
		}
	}
	return nova_geracao;
}


template<class type> std::vector<type> evolutivo<type>::transa_por_roleta(){
	//calcula a soma das notas, para agir como valor maximo do range
	//sum is used to be sure the random number generated will be smaller than the total score
	//negs is used to shift the random number in cases when the scoring system is negative
	double sum=0,negs=notas[0];
	std::vector<type> nova_geracao;
	
	int best = notas[0],best_ind=0;
		//making sure the current best individual is passed on to the next generation
	for (unsigned int i = 1; i<individuo.size(); i++){ 
		if (best < notas[i]) {
			best = notas[i];
			best_ind = i;
		}
	}
	nova_geracao.push_back(individuo[best_ind]);

//	for (unsigned int i = 0; i < notas.size(); i++) {
//		if (notas[i] < negs) negs = notas[i];
//	}

	for (unsigned int i = 0; i < notas.size(); i++) {
		if(negs<=0){
			sum += notas[i]-negs;
		}else{
			sum += notas[i];
		}
	}
	//Making sure the total sum is more than zero, and that each and every individual can be selected.

	for (unsigned int k = 0; k < individuo.size()-1; k++) {
		//gera dois numeros aleatorios, uniformemente distribuido, entre [0,sum)
		double pai = rand(), mae = rand();
		pai /= RAND_MAX;
		pai *= sum;
		mae /= RAND_MAX;
		mae *= sum;
		
		//seleciona o pai
		int i = -1;
		while (pai > 0) {
			i++;
			pai -= notas[i];
		}
		//seleciona a mae
		int j = -1;
		while (mae > 0) {
			j++;
			mae -= notas[j];
		}

		nova_geracao.push_back(individuo[j].transa(individuo[i], range));

	}
	return nova_geracao;
}

template<class type> std::vector<type> evolutivo<type>::transa_por_torneio(int n){
	std::vector<type> nova_geracao;
	unsigned int pai,mae,challenger,best=0;
	//encontra o melhor de todos, para nao matar ele sem querer
	for(unsigned int k=0;k<notas.size();k++){
		if(notas[k]>notas[best]){
			best=k;
		}
	}
	for(unsigned int k=0;k<individuo.size();k++){
		if(k==best){
			nova_geracao.push_back(individuo[k]); //melhor de todos simplesmente passa para proxima geracao
			continue;
		}
		//do contrario:
		//determina quem vai ser o pai
		pai=rand()%individuo.size();
		for(int i=0;i<n-1;i++){
			challenger=rand()%individuo.size();
			if(notas[challenger]>notas[pai]) pai=challenger;
		}
		//determina quem vai ser a mae
		mae=rand()%individuo.size();
		for(int i=0;i<n-1;i++){
			challenger=rand()%individuo.size();
			if(notas[challenger]>notas[mae])mae=challenger;
		}
		nova_geracao.push_back(individuo[pai].transa(individuo[mae],range*stable_count));
	}
	return nova_geracao;
}

#endif
