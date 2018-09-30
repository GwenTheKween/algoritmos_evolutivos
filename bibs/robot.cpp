#include "robot.h"

robo::robo(grafo& model):
    g(model){
        //coordenadas das chaves presentes no mapa
    std::vector<coord> keys=g.get_keys();
    //escolhe uma ordem aleatoria para coletar essas chaves
    std::random_shuffle(keys.begin(),keys.end());
    gene=keys;
}

void robo::simulate(){
    int i;
    std::vector<coord> leg; //a path is comprised of many legs (in portuguese, at least, an when talking about flights)
    coord start(0,0);
    path.push_back(start);
    leg=g.BFS(start,gene[0]);
    path.insert(path.end(),leg.begin(),leg.end()); //concatenates the leg after the path
    for(i=1;i<gene.size();i++){
        leg=g.BFS(gene[i-1],gene[i]);
        path.insert(path.end(),leg.begin(),leg.end());
    }
    leg=g.BFS(gene[i-1],start);
    path.insert(path.end(),leg.begin(),leg.end());
}

int robo::avalia(){
    if(path.size()==0) simulate();
    return path.size();
}
