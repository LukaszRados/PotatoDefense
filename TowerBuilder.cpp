#include "TowerBuilder.hpp"

TowerBuilder::TowerBuilder():TowerBuilder(0) {

}

TowerBuilder::TowerBuilder(int number):_towerNumber(number) {
	_sprite = sf::IntRect(40 * _towerNumber, 0, 40, 40);
}

TowerBuilder::~TowerBuilder() {

}

void TowerBuilder::firstClick() {
//	if(GameState::money < prices[0]) {
//		// Nie ma wystarczajaco kasy, by zbudowac wiezyczke
//		// w Board bedzie zmienna dotyczaca komunikatow
//	}
//	else {
////		Board::buffer = this; // - nie moze byc tak ;(
//	}
}

Clickable* TowerBuilder::secondClick(int x, int y) {
	Tower *tmp;

	switch(_towerNumber) {
	// switching numbers of towers 0 and 2 so its from left to right
	case 0:
		tmp = new Tower(0);
		break;

	case 1:
		tmp = new Tower(1);
		break;

	case 2:
		tmp = new Tower(2);
		break;
	}

	tmp->setX(x);
	tmp->setY(y);

	return tmp;
}

int TowerBuilder::getCost(int lvl) const {
	return Tower::_stats[_towerNumber][lvl][4];
}

std::string TowerBuilder::getName() const {
	return "towerBuilder";
}

int TowerBuilder::getTowerNumber() const {
	return _towerNumber;
}

int TowerBuilder::getSellingCost(int lvl) const {
	int cost = 0;
	for(int i = 0; i < lvl; ++i) {
		cost += Tower::_stats[_towerNumber][i][4];
	}
	return (float)cost * 0.6;
}

std::string TowerBuilder::getDesc() const {
	return "Cost:\t\t $" + toString(Tower::_stats[_towerNumber][0][4]) + "\n" + Tower(_towerNumber).getDesc(0);
}

