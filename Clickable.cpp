#include "Clickable.hpp"

Clickable::Clickable() {

}

Clickable::~Clickable() {

}

void Clickable::setX(unsigned int x) {
	_x = x;
}

void Clickable::setY(unsigned int y) {
	_y = y;
}

unsigned int Clickable::getX() const {
	return _x;
}

unsigned int Clickable::getY() const {
	return _y;
}

sf::IntRect Clickable::getSprite() const {
	return _sprite;
}
