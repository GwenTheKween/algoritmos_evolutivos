#include "runner.h"

runner::runner(runner const& r):
	robo::robo(r){
	m = r.m;
}

runner::runner(runner&& r):
	robo::robo(r){
	m = r.m;
}

runner& runner::operator =(runner const& r){
	m = r.m;
	robo::operator=(r);
	return (*this);
}	

runner& runner::operator =(runner&& r){
	m = r.m;
	robo::operator=(r);
	return (*this);
}


int runner::avalia(){
	return robo::avalia(this->m);
}

runner runner::transa(runner& r,int legacy){
	runner filho(r);
	filho.mutacao();
	return filho;
}

void runner::animate(){
	robo::animate(m);
}
