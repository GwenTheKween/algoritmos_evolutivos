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
        for(int i=0;i<1;i++){
            ind.push_back(runner(g));
        }
	table t;
	t.gen_random();
//	t.debug();
	g.animate(coord(0,0));
        evolutivo<runner> e(ind,processed[TIPO_TRANSA],processed[COND_FIM]);
	printf("%d\n",processed[GEN_AMNT]);
	int n;
	scanf("%d\n",&n);
	e.itera(processed[GEN_AMNT],processed[VERBOSE]);
	e.get_best().animate();
    }
    return 0;
}
