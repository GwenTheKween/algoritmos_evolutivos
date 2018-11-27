#include "robot.h"

void wait(int ms){
    usleep(ms*1000);
}

robo::robo(const robo& parent):gene(parent.gene),path(parent.path),t(parent.t){}

robo::robo(map& model){
        //coordenadas das chaves presentes no mapa
    std::vector<coord> keys=model.get_keys();
    //escolhe uma ordem aleatoria para coletar essas chaves
    std::random_shuffle(keys.begin(),keys.end());
	gene=keys;
	gene.push_back(coord(0,0));
	t.gen_random();
}

void robo::simulate(map& m){
    unsigned int i;
	//a path is comprised of many legs (in portuguese, at least, an when talking about flights)
    std::vector<coord> leg; 
    coord start(0,0);
    path.push_back(start);
    leg=m.BFS(start,gene[0]);
    path.insert(path.end(),leg.begin(),leg.end()); //concatenates the leg after the path
    m.unlock(gene[0]);
    for(i=1;i<gene.size();i++){
        leg=m.BFS(gene[i-1],gene[i]);
        path.insert(path.end(),leg.begin(),leg.end());
        m.unlock(gene[i]);
    }
//    leg=m.BFS(gene[i-1],start);
//    path.insert(path.end(),leg.begin(),leg.end());
}

int robo::avalia(map& m){
    if(path.size()==0) simulate(m);
    return -path.size();
}

void robo::debug(){
    for(unsigned int i=0;i<gene.size();i++){
        gene[i].debug('\t');
    }
    printf("\n");
}

int robo::decision(int obs){
	return t[obs];
}

void robo::random(){
        //coordenadas das chaves presentes no mapa
    //escolhe uma ordem aleatoria para coletar essas chaves
    std::random_shuffle(gene.begin(),gene.end());
}

robo robo::transa(robo& r, int legacy){ //legacy esta aqui para "legacy support", ele nao faz nada nesse caso
    robo filho(r);
    filho.t = r.t.cross_over(t);
//    filho.mutacao();
    return filho;
}

void robo::mutacao(){
    //sem cross-over, eh necessario atualizar o grafo, pois todas as chaves ja foram usadas
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

void robo::animate(map& m, std::vector<coord>& mino){
    unsigned int k=0,tmp;
    coord end(0,0);
    for(unsigned int i=0;i<path.size();i++){
        system("clear");
	path[i].debug();
	mino[i].debug('\n');
		m.animate(path[i],mino[i]);
        if(k<gene.size() && path[i] == gene[k]){
            k++;
			i--;
        }
//        if(k<gene.size())gene[k].debug(' ');
//        else end.debug(' ');
        printf("%lu\n",path.size());
	tmp = m.look_around(path[i]);
	printf("%04x,%d: (%d,%d,%d,%d)\n",tmp,t[tmp],(tmp & CONNECTED & NORTH),(tmp & CONNECTED & SOUTH),(tmp & CONNECTED & EAST),(tmp & CONNECTED & WEST));
	gene[k].debug('\n');
        wait(300);
    }
}
