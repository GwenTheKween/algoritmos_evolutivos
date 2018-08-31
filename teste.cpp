#include "bibs/evo.h"
#include "bibs/input.h"

int main(int argc, char** argv){
	std::vector<numero> init;
	numero n;
	int processed[SIZE_ARGV];
	proc_argv(argc,argv,processed);
	if(processed[HELP]){
		print_help(argv);
	}else{
		for(int i=0;i<5;i++){
			n.set(rand()%2000 - 500); //vai de -50 a 150, com o maximo sendo exatamente no meio
			init.push_back(n);
		}
		evolutivo<numero> e(init,processed[TIPO_TRANSA]);
		e.itera(20,processed[VERBOSE]);
		n=e.get_best();
	}
	return 0;
}
