#include "table.h"

table::table(const table& t){
	for(int i = 0; i < TABLESIZE; i++)
		reaction[i] = t.reaction[i];
}

table::table(table&& t){
	for(int i = 0; i < TABLESIZE; i++)
		reaction[i] = t.reaction[i];
}

void table::gen_random(){
	int i,val;
	for(i=0;i<TABLESIZE;i++){
		val = rand()%ACTION_SIZE;
		reaction[i] = val;
	}
}

table table::cross_over(table& t){
	table ret;
	int i;
	for(i=0; i<TABLESIZE; i++){
		ret.reaction[i] = (rand()%2)?
					reaction[i]:
					t.reaction[i];
	}
	return ret;
}

void table::debug(){
	for(int i=0;i<TABLESIZE; i++){
		if(i%32 == 0) printf("\n");
		printf("%d",reaction[i]);
	}
	printf("\n");
}

table table::operator = (const table& other){
	for(int i=0;i<TABLESIZE;i++) reaction[i] = other.reaction[i];
	return *this;
}

table table::operator = (table&& other){
	for(int i=0;i<TABLESIZE;i++) reaction[i] = other.reaction[i];
	return *this;
}
