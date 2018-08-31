#include "bibs/evo.h"

int main(int argc, char** argv){
	std::vector<numero> init;
	numero n;
	bool verbose;
	if(argc<2){
		verbose=false;
	}else{
		if(argv[0]=='-' && (argv[1]=='v' || argv[1]=='V')){
			verbose=true;
		}else{
			verbose=false;
		}
	}
	for(int i=0;i<5;i++){
		n.set(rand()%2000 - 500); //vai de -50 a 150, com o maximo sendo exatamente no meio
		init.push_back(n);
	}
	evolutivo<numero> e(init,ELITISMO);
	e.itera(20,verbose);
	n=e.get_best();
	return 0;
}
