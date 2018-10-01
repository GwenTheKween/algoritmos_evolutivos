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

void robo::debug(){
    int k=0;
    g.draw();
    for(int i=0;i<gene.size();i++){
        gene[i].debug('\t');
    }
    printf("\n");
    std::cout<<avalia()<<'\n';
    for(int i=0;i<path.size();i++){
        path[i].debug(' ');
        if(path[i]==gene[k]){
            printf("\n");
            g.unlock(path[i]);
            g.draw();
            path[i].debug(' ');
            k++;
        }
    }
    printf("\n");
}

void robo::mutacao(grafo& model){
    //sem cross-over, eh necessario atualizar o grafo, pois todas as chaves ja foram usadas
    g=model;
    int i,j;
    coord temp;
    //chooses 2 random coordinates to change
    i=rand()%gene.size();
    //-1 and possibly adding 1 to j assures that coordinates mus be different
    j=rand()%(gene.size()-1);
    j+=(j>=i);

    //swaps the 2 positions
    temp=gene[i];
    gene[i]=gene[j];
    gene[j]=temp;

    //clears the path, so a new one can be generated
    path.clear();
}
