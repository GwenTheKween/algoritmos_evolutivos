//ESSE ARQUIVO EH TEMPORARIO, SO PARA TESTAR SE A CLASSE GRAFO ESTA FUNCIONANDO

#include "robot.h"
#include "input.h"
#include "evo.h"
#include <time.h>

int main(int argc,char** argv){
    grafo g(10);
    int processed[SIZE_ARGV];
    std::vector<robo> ind;
    proc_argv(argc,argv,processed);
    if(processed[HELP]){
        print_help(argv[0]);
    }else{
        g.gen_map(10);
        for(int i=0;i<4;i++){
            robo r(g);
            ind.push_back(r);
        }
        evolutivo<robo> e(ind,processed[TIPO_TRANSA],processed[COND_FIM]);
        e.itera(processed[GEN_AMNT],processed[VERBOSE]);
    }
    return 0;
}
