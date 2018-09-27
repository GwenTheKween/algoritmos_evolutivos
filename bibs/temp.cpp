//ESSE ARQUIVO EH TEMPORARIO, SO PARA TESTAR SE A CLASSE GRAFO ESTA FUNCIONANDO

#include "grafo.h"

int main(){
    grafo g(10);
    g.gen_map(NULL);
    g.draw();
    printf("%d\n",g.BFS(0,0,3,3));
    return 0;
}
