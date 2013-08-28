#include "Layer.hpp"

/**
 * Layer is created with 1 parameter: pointer to RenderWindow object
 */
Layer::Layer(sf::RenderWindow *w) {
	_window = w;
}

Layer::~Layer() {

}

/**
 * 1. Passes event to next layer
 * 2. Uses event information to do some stuff
 */
void Layer::parseEvent(sf::Event &event) {

}

/**
 * 1. Calls next layer
 * 2. Draws own stuff
 */
void Layer::draw() {

}

void Layer::update(){

}
