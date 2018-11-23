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
	std::vector<int> valid;
	for(i=0;i<TABLESIZE;i++){
		valid.clear();
		if(i & (CONNECTED & NORTH)) valid.push_back(MOVE_UP);

		if(i & (CONNECTED & SOUTH)) valid.push_back(MOVE_DOWN);

		if(i & (CONNECTED & EAST)) valid.push_back(MOVE_RIGHT);

		if(i & (CONNECTED & WEST)) valid.push_back(MOVE_LEFT);

		/*
		valid.push_back(MOVE_UP);
		valid.push_back(MOVE_DOWN);
		valid.push_back(MOVE_LEFT);
		valid.push_back(MOVE_RIGHT);
		*/

		if(valid.size() > 0){
			val = valid[rand()%valid.size()];
		}else{
			val = 0;
		}
//		val = (valid.size()) ? (valid[rand()%valid.size()]) : (0);
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
		if(i%16 == 0) printf("\n");
		printf("%04x: %d\t",i,reaction[i]);
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
