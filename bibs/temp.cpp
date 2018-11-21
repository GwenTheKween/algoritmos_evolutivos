//ESSE ARQUIVO EH TEMPORARIO, SO PARA TESTAR SE A CLASSE GRAFO ESTA FUNCIONANDO

#include "runner.h"
#include "input.h"
#include "evo.h"
#include <time.h>

int main(int argc,char** argv){
    map g(10);
    int processed[SIZE_ARGV];
    std::vector<runner> ind;
    proc_argv(argc,argv,processed);
//	srand(time(NULL));
    if(processed[HELP]){
        print_help(argv[0]);
    }else{
        g.gen_map(10);
        for(int i=0;i<40;i++){
            ind.push_back(runner(g));
        }
	g.animate(coord(0,0));
//        evolutivo<runner> e(ind,processed[TIPO_TRANSA],processed[COND_FIM]);
//	e.itera(processed[GEN_AMNT],processed[VERBOSE]);
//	runner r2(e.get_best());
//	r2.animate();
        //e.itera(processed[GEN_AMNT]*10,processed[VERBOSE]);
        //robo d2(e.get_best());
//        d2.animate();
    }
    return 0;
}
