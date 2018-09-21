#ifndef INPUT_PROCESSING
#define INPUT_PROCESSING
#include <string>

enum ARGV{
	VERBOSE, 
	TIPO_TRANSA,	//tipo de transa a ser usado
    COND_FIM,
	HELP,
    GEN_AMNT,
    MUT_RANGE,
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
    //load standard values
	for(int i=0;i<SIZE_ARGV;i++){
        if(i==GEN_AMNT) proc[i]=20;
        else if(i==MUT_RANGE) proc[i]=100;
        else proc[i]=0;
    }
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
			}else if(s=="-n"){
                i++;
                if(i<argc){
                    proc[GEN_AMNT]=atoi(argv[i]);
                }
            }else if(s=="-m"){
                i++;
                if(i<argc){
                    proc[MUT_RANGE]=atoi(argv[i]);
                }
            }else if(s=="-f"){
                proc[COND_FIM]=FIXED;
            }else if(s=="-s"){
                proc[COND_FIM]=STABLE;
            }
		}
	}
	if((proc[TIPO_TRANSA]*proc[COND_FIM])==0) proc[HELP]=1;
}

void print_help(char** argv){
	printf("USAGE: %s -t <type> <endCondition> [<options>]\n",argv[0]);
	printf("\t-t:\t\t type of cross-over used for the algorithm, there are 3 possible types:\n");
	printf("\t\telitismo(e): the best performing is used to cross-over with all others\n");
	printf("\t\troleta(r): Original proposed method, 2 individuals are chosen at random, with the best performing being more likely\n");
	printf("\t\ttorneio(t): chooses 2 sets of n individuals (default is 2) at random, and the best performing of each set is chosen for the cross-over\n");
    printf("\tEndCondition: -f/-s either -f for fixed amount of generations, or -s for stability condition\n");
	printf("\nADDITIONAL OPTIONS:\n");
	printf("\t-v: verbose\n");
	printf("\t-h: show this page\n");
    printf("\t-n <num>: number of generations to be simulated, if -f is chosen, or maximum number of stable generations, if -s is chosen\n");
    printf("\t-m <num>: range of motation times 100\n");
	printf("\n\nPS: roleta is not fully implemented yet\n");
}

#endif
