//ESSE ARQUIVO EH TEMPORARIO, SO PARA TESTAR SE A CLASSE GRAFO ESTA FUNCIONANDO

#include "robot.h"
#include <time.h>

int main(){
    grafo g(10);
    std::vector<coord> keys,doors;
    g.gen_map(10);
    robo r(g);
    r.simulate();
    r.debug();
    r = r.transa(r,g);
    r.simulate();
    r.debug();
    return 0;
}
