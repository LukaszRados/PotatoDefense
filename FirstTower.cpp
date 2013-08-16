#include "FirstTower.hpp"

FirstTower::FirstTower():Tower() {
	_range = 20;
	_damage = 10;
	_reloadTime = 5;
	_sprite = sf::IntRect(0, 0, 40, 40);
}

FirstTower::~FirstTower() {

}

void FirstTower::firstClick() {

}

Clickable* FirstTower::secondClick(int x, int y) {

}
