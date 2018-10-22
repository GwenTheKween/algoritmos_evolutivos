#include "bibs/input.h"
#include "bibs/robot.h"

#define IND_AMNT 4
#define RAND_MAP 1
#define MAP_SIZE 10
#define DOOR_AMNT 10

void menu(int* proc){
    for(int i=0;i<SIZE_ARGV;i++){
        if(i==GEN_AMNT) proc[i]=20;
        else if(i==MUT_RANGE) proc[i]=100;
        else proc[i]=0;
    }
    proc[TIPO_TRANSA]=ROLETA;
    proc[COND_FIM]=FIXED;
}

int main(int argc, char** argv){
    int processed[SIZE_ARGV];
    std::vector<robo> init;
    if(argc>1){
        proc_argv(argc,argv,processed);
    }else{
        menu(processed);
    }

    if(processed[HELP]){
        print_help(argv[0]);
    }else{
        grafo g(MAP_SIZE);
        if(RAND_MAP){
            g.gen_map(DOOR_AMNT);
        }
        for(int i=0;i<IND_AMNT;i++){
            robo r(g);
            init.push_back(r);
        }
        evolutivo<robo> e(init,processed[TIPO_TRANSA],processed[COND_FIM]);
        e.itera(processed[GEN_AMNT],processed[VERBOSE]);
    }
    return 0;
}
