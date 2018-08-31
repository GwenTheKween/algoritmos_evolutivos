#include "bibs/evo.h"
#include <string>

enum ARGV{
	VERBOSE, 
	TIPO_TRANSA,	//tipo de transa a ser usado
	HELP,
	SIZE_ARGV
};

std::string lower_all(char* s){
	std::string ret="";
	for(int i=0;s[i];i++){
		if(s[i]<='Z' && 'A'<=s[i]){
			ret+=(s[i]^' '); //xor com espaco faz maiuscula virar minuscula e vice-versa
		}else
			ret+=s[i];
	}
	return ret;
}

void proc_argv(int argc,char** argv,int* proc){
	std::string s,tmp;
	for(int i=0;i<SIZE_ARGV;i++) proc[i]=0;
	if(argc<2){
		proc[HELP]=1;
	}else{
		for(int i=0;i<argc;i++){
			s=lower_all(argv[i]);
			if(s=="-v"){
				proc[VERBOSE]=1;
			}else if(s=="-h" || s=="-help"){
				proc[HELP]=1;
			}else if(s=="-t"){
				i++;
				if(i<argc){ //sanity check
					s=lower_all(argv[i]);
					if(s=="e" || s=="elitismo"){
						proc[TIPO_TRANSA]=ELITISMO;
					}else if(s=="r" || s=="roleta"){
						proc[TIPO_TRANSA]=ROLETA;
					}else if(s=="t" || s=="torneio"){
						proc[TIPO_TRANSA]=TORNEIO;
					}
				}
			}
		}
	}
	if(proc[TIPO_TRANSA]==0) proc[HELP]=1;
}

void print_help(char** argv){
	printf("USAGE: %s -t <type> [<options>]",argv[0]);
	printf("\t-t:\t\t type of cross-over used for the algorithm, there are 3 possible types:\n");
	printf("\t\telitismo(e): the best performing is used to cross-over with all others\n");
	printf("\t\troleta(r): Original proposed method, 2 individuals are chosen at random, with the best performing being more likely\n");
	printf("\t\ttorneio(t): chooses 2 sets of n individuals (default is 2) at random, and the best performing of each set is chosen for the cross-over\n");
	printf("\nADDITIONAL OPTIONS:\n");
	printf("\t-v: verbose\n");
}

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
