#include "Tower.hpp"

Tower::Tower():Tower(0) {

}

Tower::Tower(int no):_no(no) {
	_firstShot=true;
	_range = 50;
	_damage = 10;
	_reloadTime = 1000;
	_sprite = sf::IntRect(_no * 40, 0, 40, 40);
}

Tower::~Tower() {

}

void Tower::shoot(std::list<Worm> & enemies) {
	if(_firstShot || _time.getElapsedTime().asMilliseconds() >= _reloadTime){
		_firstShot=false;
		_time.restart();
std::cout << "poof!" << std::endl;
		std::vector<Worm *> inRange;
		for(auto & i : enemies){
			if(i.distance(_x,_y) < _range){
				inRange.push_back(&i);
			}
		}
std::cout << "w zasiegu " << inRange.size() << std::endl;
		if(inRange.size()){
			Worm * target=inRange[0];

			std::cout << target << std::endl;

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
	++_level;
	_sprite = sf::IntRect(_no * 40, (_level - 1) * 40, 40, 40);
}

/**
 * Returns information that should be displayed after hover
 */
std::string Tower::getDesc() const {
	return "Range:\t\t 20 \nReload:\t\t2s";
}
