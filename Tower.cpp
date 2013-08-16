#include "Tower.hpp"

Tower::Tower():Tower(0) {

}

Tower::Tower(int no):_no(no) {
	_range = 20;
	_damage = 10;
	_reloadTime = 5;
	_sprite = sf::IntRect(_no * 40, 0, 40, 40);
}

Tower::~Tower() {

}

void Tower::shoot(int **enemies) {

}

void Tower::firstClick() {

}

Clickable* Tower::secondClick(int x, int y) {
	return 0;
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

std::string Tower::getDesc() const {
	return "Level:\t\t  " + toString(_level) + "\n"
			+ "Range:\t\t 20 \n"
			+ "Reload:\t\t2s";
}
