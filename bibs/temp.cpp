//ESSE ARQUIVO EH TEMPORARIO, SO PARA TESTAR SE A CLASSE GRAFO ESTA FUNCIONANDO

#include "robot.h"
#include <time.h>

int main(){
    grafo g(10,20);
    std::vector<coord> keys,doors;
    g.gen_map(10);
    robo r(g);
    r.simulate();
    r.debug();
//    r.mutacao(g);
//    r.debug();
    return 0;
}
