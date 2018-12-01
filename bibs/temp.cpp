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
	srand(3);
//	srand(time(NULL));
    if(processed[HELP]){
        print_help(argv[0]);
    }else if(processed[READ]){
	runner r(g);
	std::ifstream f;
	f.open(argv[processed[READ]]);
	r.read(f);
	f.close();
	r.animate();
    }else{
        g.gen_map(10);
        for(int i=0;i<400;i++){
            ind.push_back(runner(g));
        }
        evolutivo<runner> e(ind,processed[TIPO_TRANSA],processed[COND_FIM]);
	e.itera(processed[GEN_AMNT],processed[VERBOSE]);
	if(processed[SAVE]){
		std::ofstream f;
		f.open(argv[processed[SAVE]]);
		e.get_best().save(f);
		f.close();
	}
	if(processed[ANIMATE])
		e.get_best().animate();
    }
    return 0;
}
