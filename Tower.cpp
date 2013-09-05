#include "Tower.hpp"

int Tower::_stats [3][3][5]= {
		// { range, damage, reloadTime, anti-air(0/1/2), price ($)}
		{ //tower 1 -universal since 2nd level
				{70,	4,	800,	0,	15}, // level 1
				{75,	7,	700,	2,	80}, // level 2
				{85,	10,	600,	2,	150} //level 3
		},
		{ //tower 2 - anti air
				{110,	12,	700,	1,	90}, //level 1
				{135,	20,	700,	1,	200}, //level 2
				{160,	30,	700,	1,	800} // level 3
		},
		{ //tower 3 - shooting ground
				{70,	12,	900,	0,	100}, //level 1
				{100,	25,	800,	0,	300}, // level 2
				{120,	30,	700,	0,	1000} // level 3
		}
};

std::string Tower::_desc[3][3] = {
		{
				"Shoots only walking enemies\nor both at levels 2 & 3",
				"Now it shoots also flying enemies.",
				"Shoots both types of enemies\nDamage increased 2.5 times!"
		},
		{
				"Shoots only flying enemies",
				"Shoots only flying enemies.\nDamage increased twice",
				"Shoots only flying enemies.\nDamage increased again!"
		},
		{
				"Shoots only walking enemies",
				"Shoots only walking enemies.\nDamage increased almost 3 times!",
				"Shoots only walking enemies.\nSuper-powerful!"
		},
};

void Tower::setStats(int tower, int level){
	_range=_stats[tower][level-1][0];
	_damage=_stats[tower][level-1][1];
	_reloadTime=_stats[tower][level-1][2];
	_antiAir=_stats[tower][level-1][3];
}


Tower::Tower():Tower(0) {

}

Tower::Tower(int no):_no(no), _target(nullptr) {
	setStats(no,1);
	_sprite = sf::IntRect(_no * 40, 0, 40, 40);
//	_sound.setBuffer(*(GameState::sounds["laser" + toString(_no + 1)]));
//	_sound.setVolume(50);
//	_sound.setLoop(false);
}

Tower::~Tower() {

}

void Tower::shoot(std::list<Worm> & enemies) {
	if(GameState::state==Game){
		if(_time.isPaused()){
			_time.start();
		}

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
				_target=inRange[0];



				for(unsigned int i=0;i<inRange.size();i++){
					if(inRange[i]->getDist() < _target->getDist())
						_target=inRange[i];
				}

				if(!_target->dmg(_damage)){
					GameState::money+=_target->getValue();
//					_target=nullptr;
				}
			} else {
				_target=nullptr;
			}
		}
	} else if(GameState::state==Paused || GameState::state==GameOver){
		if(!_time.isPaused()){
				_time.pause();
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

int Tower::getRange() const {
	return getRange(1);
}

int Tower::getRange(int lvl) const {
	return _stats[_no][lvl - 1][0];
}

void Tower::levelUp() {
	setStats(_no,++_level);
	_sprite = sf::IntRect(_no * 40, (_level - 1) * 40, 40, 40);
}

/**
 * Returns information that should be displayed after hover
 */

std::string Tower::getDesc(int lvl) const {
	return "Damage: \t\t"+toString(_stats[_no][lvl][1])+"\nRange:\t\t " + toString(_stats[_no][lvl][0]) + " \nReload:\t\t"+toString(_stats[_no][lvl][2])+"\nInfo:\n" + _desc[_no][lvl];
}

sf::Vector2f Tower::getPosition(){
	return sf::Vector2f(_x*40+20,_y*40+20);
}

void Tower::save(std::ostream & out) const {
	out << _x << " "<< _y << " " << _no << " " << _level;
}
bool Tower::load(std::istream & in) {
	in >> _x >> _y >> _no >> _level;
	return in;
}
