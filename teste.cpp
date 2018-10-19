#include "bibs/evo.h"
#include "bibs/input.h"

int main(int argc, char** argv){
	std::vector<numero> init;
	numero n;
	int processed[SIZE_ARGV];
	proc_argv(argc,argv,processed);
	if(processed[HELP]){
		print_help(argv[0]);
	}else{
		for(int i=0;i<5;i++){
			n.set(rand()%1200 - 100); //vai de -100 a 1100
			init.push_back(n);
		}
		evolutivo<numero> e(init,processed[TIPO_TRANSA],processed[COND_FIM],processed[MUT_RANGE]);
		e.itera(processed[GEN_AMNT],processed[VERBOSE]);
		n=e.get_best();
	}
	return 0;
}
