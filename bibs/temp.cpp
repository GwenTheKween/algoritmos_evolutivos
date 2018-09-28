//ESSE ARQUIVO EH TEMPORARIO, SO PARA TESTAR SE A CLASSE GRAFO ESTA FUNCIONANDO

#include "grafo.h"

int main(){
    grafo g(10);
    g.gen_map();
    printf("\n\n");
    g.debug();
    g.draw();
    coord c(0,0);
    tile t;
    t=g[c];
    printf("%d %d %d %d\n",t.right(),t.left(),t.down(),t.up());
    //printf("%d\n",g.BFS(0,0,3,3));
    return 0;
}
