#include "Clickable.hpp"

Clickable::Clickable() {

}

Clickable::~Clickable() {

}

void Clickable::setX(int x) {
	_x = x;
}

void Clickable::setY(int y) {
	_y = y;
}

int Clickable::getX() const {
	return _x;
}

int Clickable::getY() const {
	return _y;
}

sf::IntRect Clickable::getSprite() const {
	return _sprite;
}

std::string Clickable::getDesc() const {
	return _desc;
}

void Clickable::save(std::ostream & a) const {

}

bool Clickable::load(std::istream & a) {
	return false;
}
