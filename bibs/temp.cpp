//ESSE ARQUIVO EH TEMPORARIO, SO PARA TESTAR SE A CLASSE GRAFO ESTA FUNCIONANDO

#include "grafo.h"

int main(){
    grafo g(10);
    coord key(2,2);
    std::vector<coord> path;
    g.gen_map();
    g.draw();
    path=g.BFS(0,0,2,6);
    for(int i=0;i<path.size();i++){
        path[i].debug(' ');
    }
    printf("\n");
    g.unlock(key);
    g.draw();
    path=g.BFS(0,0,2,6);
    for(int i=0;i<path.size();i++){
        path[i].debug(' ');
    }
    printf("\n");
    return 0;
}
