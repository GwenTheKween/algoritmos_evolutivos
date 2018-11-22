#include "runner.h"

runner::runner(runner const& r):
	robo::robo(r),
	position(0,0),
	keys_acquired(0)
{
	m = r.m;
}

runner::runner(runner&& r):
	robo::robo(r),
	position(0,0),
	keys_acquired(0)
{
	m = r.m;
}

runner& runner::operator =(runner const& r){
	m = r.m;
	robo::operator=(r);
	position = r.position;
	return (*this);
}	

runner& runner::operator =(runner&& r){
	m = r.m;
	robo::operator=(r);
	position = r.position;
	return (*this);
}


int runner::avalia(){
	//return robo::avalia(this->m);
	coord key_location;
	int score = 0,movement;
	char observed;
	std::vector<coord> pth;
	pth.push_back(position);
	key_location = get_gene()[0];
	//get_gene()[0].debug();
	while(score < 1000){
		score++;
		observed = m.look_around(position);
		observed |= ( 	(NORTH & KEY_DIR) * (key_location.y() < position.y()) |
				(SOUTH & KEY_DIR) * (key_location.y() > position.y()) |
				(EAST & KEY_DIR) * (key_location.x() < position.x())  |
				(WEST & KEY_DIR) * (key_location.x() > position.x()));
		movement = decision(observed);
		//printf("%d\t",movement);
		if(movement == MOVE_RIGHT){
			if(m[position].connected(RIGHT)){
				position = position.move(RIGHT);
			}
		} else if(movement == MOVE_LEFT){
			if(m[position].connected(LEFT)){
				position = position.move(LEFT);
			}
		}else if(movement == MOVE_DOWN){
			if(m[position].connected(DOWN)){
				position = position.move(DOWN);
			}
		}else if(movement == MOVE_UP){
			if(m[position].connected(UP)){
				position = position.move(UP);
			}
		}

		if(position == get_gene()[keys_acquired]){
			coord end(0,0);
			if(position == end)
				break;
			else
				m.unlock(position);
		}
		pth.push_back(position);
	}
	set_path(pth);
	score -= 50*keys_acquired;
	//printf("%d\n",score);
	return -score;
}

runner runner::transa(runner& r,int legacy){
	runner filho(r);
	filho.mutacao(legacy/100);
	return filho;
}

void runner::mutacao(int amnt){
	int entry, new_val;
	for(int k=0;k<amnt;k++){
		entry = rand()%TABLESIZE;
		new_val = rand()%(ACTION_SIZE-1);
		if(new_val >= get_t()[entry]) new_val++;
		set_table_entry(entry,new_val);
	}
}

void runner::animate(){
	robo::animate(m);
}
