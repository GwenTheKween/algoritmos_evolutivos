#ifndef INPUT_PROCESSING
#define INPUT_PROCESSING
#include <string>
#include <iostream>
#include "evo.h"


//Which arguments are currently implemented
enum ARGV{
	VERBOSE, 
	TIPO_TRANSA,	//tipo de transa a ser usado
    COND_FIM,
	HELP,
    GEN_AMNT,
    MUT_RANGE,
    ANIMATE,
    SAVE,
    READ,
	SIZE_ARGV       //how many arguments are accepted at most
};


/*  Function lower_all. Receives a c string and turns it into std::string that is all lowercase
    @Parameters:
        char* s: the received c string
    @return the converted std::string
*/
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


/*  Function proc_argv, processes arguments passed in the command line
    @Parameters:
        int argc, how many arguments were passed
        char** argv, what are these arguments
        int* proc, processed values, translated to int
    @return void
*/
void proc_argv(int argc,char** argv,int* proc){
	std::string s;
    //load default values
	for(int i=0;i<SIZE_ARGV;i++){
        if(i==GEN_AMNT) proc[i]=20;
        else if(i==MUT_RANGE) proc[i]=100;
        else proc[i]=0;
    }

	if(argc<2){//if no arguments were passed, show the help screen
		proc[HELP]=1;
	}else{
		for(int i=0;i<argc;i++){
			s=lower_all(argv[i]);
			if(s=="-v"){ //verbose must be true
				proc[VERBOSE]=1;
			}else if(s=="-h" || s=="-help"){ //help page was requested
				proc[HELP]=1;
			}else if(s=="-t"){ //what tipe of cross-over will be used
				i++;
				if(i<argc){ //ensures that the user passed an extra argument for the cross-over
					s=lower_all(argv[i]);
					if(s=="e" || s=="elitismo"){
						proc[TIPO_TRANSA]=ELITISMO;
					}else if(s=="r" || s=="roleta"){
						proc[TIPO_TRANSA]=ROLETA;
					}else if(s=="t" || s=="torneio"){
						proc[TIPO_TRANSA]=TORNEIO;
					}
				}
           		}else if(s=="-f"){ //the user wants a ficed amount of generations to be run
		                proc[COND_FIM]=FIXED;
	   		}else if(s=="-s"){ //the user wants the simulation to stop after it has stabilized for a certain amount of generations
        	        	proc[COND_FIM]=STABLE;
			}else if(s=="-n"){ //the amount of generations was specified
        		        i++;
				if(i<argc){ //ensures that the user passed an extra argument for the cross-over
	        	            proc[GEN_AMNT]=atoi(argv[i]);
		                }
            		}else if(s=="-m"){//the mutation range was specified
                		i++;
				if(i<argc){ //ensures that the user passed an extra argument for the cross-over
                    			proc[MUT_RANGE]=atoi(argv[i]);
                		}
            		}else if(s=="-a"){ //The runner will be simulated at the end of the run
				proc[ANIMATE]=1;
			}else if(s=="-o"){ //The user wishes to save, the file name must be the next argument
				i++;
				if(i<argc){
					proc[SAVE] = i;
				}
			}else if(s=="-i"){ //The user wishes to simulate a runner from a file, the next argument ,ust be the file name
				i++;
				if(i<argc){
					proc[READ] = i;
				}
			}
		}
	}
	if(!((proc[TIPO_TRANSA]&&proc[COND_FIM]) || proc[READ])) proc[HELP]=1; //if the cross-over or the end condition was not set, the simulation won't run and the help screen will be printed
}


/*  Function print_help, prints the help screen, with all info that the user may need
    @Parameters:
        char* prog_name: the name of the program being run
    @Return: void
*/
void print_help(char* prog_name){
	printf("USAGE: %s -t <type> <endCondition> [<options>]\n",prog_name);
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
	printf("\t-o <file>: file to save the runner to, once the simulation is over\n");
	printf("\t-i <file>: file to read the runner from, instead of evolving everything from scratch\n");
	printf("\t-a: if the end of the evolution will be animated\n");
}

#endif
