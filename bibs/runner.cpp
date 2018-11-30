#include "runner.h"

runner::runner(runner const& r):
	robo::robo(r),
	m(r.m),
	position(r.position),
	keys_acquired(r.keys_acquired),
	mino_path(r.mino_path)
{
}

runner::runner(runner&& r):
	robo::robo(r),
	m(r.m),
	position(r.position),
	keys_acquired(r.keys_acquired),
	mino_path(r.mino_path)
{
}

runner& runner::operator =(runner const& r){
	m = r.m;
	robo::operator=(r);
	position = r.position;
	mino_path = r.mino_path;
	return (*this);
}	

runner& runner::operator =(runner&& r){
	m = r.m;
	robo::operator=(r);
	position = r.position;
	mino_path = mino_path;
	return (*this);
}


int runner::avalia(){
	coord key_location,Mino;
	int score = 0,movement;
	int observed;
	std::vector<coord> pth;
	position.set(0,0);
	keys_acquired = 0;
	pth.push_back(position);
	mino_path.clear();
	mino_path.push_back(m.get_Minotaur());
	key_location = get_gene()[0];
	while(score < 1000){
		score++;
		observed = m.look_around(position);
		observed |= position.relative_dir(key_location) << KEY_DIR;
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
		Mino = m.updateMinotaur(position);
		pth.push_back(position);
		mino_path.push_back(Mino);
		if(position == Mino){
			score -= 800;
			break;
		}
	}
	set_path(pth);
	score += 1000*keys_acquired;
	return score;
}

runner runner::transa(runner& r,int legacy){
	runner filho(r);
	filho.mutacao(legacy/100);
	return filho;
}

void runner::mutacao(int amnt){
	int entry, new_val;
	std::vector<int> valid;
	for(int k=0;k<amnt;k++){
		entry = rand()%TABLESIZE;
		if(entry & (CONNECTED & NORTH)) valid.push_back(MOVE_UP);

		if(entry & (CONNECTED & SOUTH)) valid.push_back(MOVE_DOWN);

		if(entry & (CONNECTED & EAST)) valid.push_back(MOVE_RIGHT);

		if(entry & (CONNECTED & WEST)) valid.push_back(MOVE_LEFT);
		if(valid.size() > 0){
			new_val = rand()%(valid.size());
			new_val = valid[new_val];
		}else
			new_val = 0;
		set_table_entry(entry,new_val);
		valid.clear();
	}
}

void runner::animate(){
	robo::animate(m,mino_path);
}

void runner::save(std::ofstream& f){
	m.save(f);
	position.save(f);
	position.debug();
	f << keys_acquired;
	f << '\n';
	f << mino_path.size();
	f << '\n';
	std::cout << keys_acquired << '\t' << mino_path.size()<<'\n';
	for(unsigned int i = 0;i<mino_path.size(); i++){
		mino_path[i].save(f);
	}
	robo::save(f);
}

void runner::read(std::ifstream& f){
	int size;
	coord tmp;
	m.read(f);
	position.read(f);
	f >> keys_acquired;
	f >> size;
	for(int i=0 ;i<size;i++){
		tmp.read(f);
		mino_path.push_back(tmp);
	}
	robo::read(f);
}
