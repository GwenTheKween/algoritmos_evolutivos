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
	int score = 0,movement;
	char observed;
	std::vector<coord> pth;
	pth.push_back(position);
	while(score < 1000){
		score++;
		observed = m.look_around(position);
		movement = decision(observed);
		if(movement == MATCH_X){
			if(position.x() > get_gene()[keys_acquired].x()){
				if(!m.can_move(position,RIGHT))
					movement = MATCH_Y;
				else
					position = position.move(RIGHT);
			}else{
				if(!m.can_move(position,LEFT))
					movement = MATCH_Y;
				else
					position = position.move(LEFT);
			}
		}
		if(movement == MATCH_Y){
			if(position.y() > get_gene()[keys_acquired].y()){
				if(!m.can_move(position,UP))
					movement = RUN_TO_BIF;
				else
					position = position.move(UP);
			}else{
				if(!m.can_move(position,DOWN))
					movement = RUN_TO_BIF;
				else
					position = position.move(DOWN);
			}
		}else if(movement == RUN_TO_BIF){
			if(observed & (NORTH & BIFURCATION)){
				position = position.move(UP);
			}else if(observed & (SOUTH & BIFURCATION)){
				position = position.move(DOWN);
			}else if(observed & (EAST & BIFURCATION)){
				position = position.move(LEFT);
			}else if(observed & (WEST & BIFURCATION)){
				position = position.move(RIGHT);
			}
		}else if(movement == RUN_FROM_M){
			if(m.can_move(position,UP))
				position = position.move(UP);
			else if(m.can_move(position,DOWN))
				position = position.move(DOWN);
			else if(m.can_move(position,LEFT))
				position = position.move(LEFT);
			else if(m.can_move(position,RIGHT))
				position = position.move(RIGHT);
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
	printf("%d\n",score);
	return score;
}

runner runner::transa(runner& r,int legacy){
	runner filho(r);
	filho.mutacao();
	return filho;
}

void runner::animate(){
	robo::animate(m);
}
