#include "Wall.hpp"

Wall::Wall() {
	_sprite = sf::IntRect(0, 0, 40, 40);
}

Wall::~Wall() {

}

void Wall::firstClick() {
	std::cout << "Oh, stop it you!" << std::endl;
}

Clickable* Wall::secondClick(int x, int y) {
	std::cout << "Come on, stop!" << std::endl;
	return 0;
}

std::string Wall::getName() const {
	return "wall";
}
