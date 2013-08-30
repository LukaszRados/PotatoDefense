#include "Tower.hpp"

int Tower::_stats [3][3][4]= {
		// { range, damage, reloadTime, anti-air(0/1)}
		{ //tower 1 -universal since 2nd level
				{50, 1,500,0}, // level 1
				{100, 4, 350, 2}, // level 2
				{100, 10, 280, 2} //level 3
		},
		{ //tower 2 - anti air
				{100,4,800,1}, //level 1
				{130, 8, 600, 1}, //level 2
				{100, 15, 400, 1} // level 3
		},
		{ //tower 3 - shooting ground
				{50,3, 900,0}, //level 1
				{100,8,800,0}, // level 2
				{120, 20, 450, 0} // level 3
		}
};

// Towers costs
// in 'murican dollars of course :)
int Tower::_prices[3][3] = {
		// tower 1
		{75, 100, 150},
		// tower 2
		{90, 130, 180},
		// tower 3
		{110, 150, 200}
};


void Tower::setStats(int tower, int level){
	_range=_stats[tower][level-1][0];
	_damage=_stats[tower][level-1][1];
	_reloadTime=_stats[tower][level-1][2];
	_antiAir=_stats[tower][level-1][3];


	std::cout << "stats set ["<<tower<<"][" << level-1 << "]: range " << _range << std::endl <<
			" damage: " << _damage << " reloadTime " << _reloadTime << " antiAir " << _antiAir << std::endl;
}


Tower::Tower():Tower(0) {

}

Tower::Tower(int no):_no(no) {
//	_firstShot=true;
//	_range = 50;
//	_damage = 10;
//	_reloadTime = 1000;

	std::cout << "wieza x: " << _x << " y: " << _y << " no: " << _no << std::endl;

	setStats(no,1);
	_sprite = sf::IntRect(_no * 40, 0, 40, 40);
}

Tower::~Tower() {

}

void Tower::shoot(std::list<Worm> & enemies) {
	if(_firstShot || _time.getElapsedTime().asMilliseconds() >= _reloadTime){
		_firstShot=false;
		_time.restart();

		std::vector<Worm *> inRange;
		for(auto & i : enemies){
			if(i.distance(_x,_y) < _range && (i.isFlying()==(bool)_antiAir || _antiAir==2)){
				inRange.push_back(&i);
			}
		}

		if(inRange.size()){
			Worm * target=inRange[0];



			for(int i=0;i<inRange.size();i++){
				if(inRange[i]->getDist() < target->getDist())
					target=inRange[i];
			}

			if(!target->dmg(_damage)){
				GameState::money+=target->getValue();
			}
		}
	}

}

std::string Tower::getName() const {
	return "tower";
}

int Tower::getLevel() const {
	return _level;
}

int Tower::getNumber() const {
	return _no;
}

void Tower::levelUp() {
	setStats(_no,++_level);
	_sprite = sf::IntRect(_no * 40, (_level - 1) * 40, 40, 40);
}

/**
 * Returns information that should be displayed after hover
 */

std::string Tower::getDesc(int lvl) const {
	std::string desc[3] = {
		"Shooting only ground\nor both at level 2 & 3",
		"Shooting only air",
		"Shooting both ground and air"
	};
	std::cout << _no << std::endl;
	return "Range:\t\t " + toString(_stats[_no][0][0]) + " \nReload:\t\t2s\nInfo:\n" + desc[_no];
}
