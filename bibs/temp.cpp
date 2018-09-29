//ESSE ARQUIVO EH TEMPORARIO, SO PARA TESTAR SE A CLASSE GRAFO ESTA FUNCIONANDO

#include "grafo.h"

int main(){
    grafo g(10);
    coord key(2,2);
    g.gen_map();
    g.draw();
    g.unlock(key);
    g.draw();
    return 0;
}
