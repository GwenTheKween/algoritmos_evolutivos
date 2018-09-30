//ESSE ARQUIVO EH TEMPORARIO, SO PARA TESTAR SE A CLASSE GRAFO ESTA FUNCIONANDO

#include "grafo.h"
#include <time.h>

int main(){
    grafo g(10);
    std::vector<coord> keys,doors;
    srand(time(NULL));
    g.gen_map();
    g.draw();
    keys=g.get_keys();
    doors=g.get_doors();
    for(int i=0;i<keys.size();i++){
        keys[i].debug('\t');
        doors[i].debug('\n');
    }
    return 0;
}
