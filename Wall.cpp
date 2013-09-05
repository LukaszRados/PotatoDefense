#include "Wall.hpp"

Wall::Wall():Wall(1) {
}

Wall::Wall(int n):_number(n) {
	_sprite = sf::IntRect(0, 0, 40, 40);
}

Wall::~Wall() {

}

std::string Wall::getName() const {
	return "wall";
}

int Wall::getNumber() const {
	return _number;
}
