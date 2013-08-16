#include "DialogLayer.hpp"

DialogLayer::DialogLayer(sf::RenderWindow *w):Layer(w) {
	_next = new TowerLayer(w);
}

DialogLayer::~DialogLayer() {

}

void DialogLayer::parseEvent(sf::Event &event) {
	if(_next != 0) {
		_next->parseEvent(event);
	}

	// Mamy cos do roboty tylko wtedy, gdy w buforze znajduje sie jakis obiekt
	// Tzn, cos zostalo juz klikniete

	if(Board::buffer == 0) return;

	switch(event.type) {
	case sf::Event::KeyPressed:
		if(event.key.code == sf::Keyboard::Space) {
			_window->setTitle("Spacja :)");
		}
		break;
	}
}

void DialogLayer::draw() {
	if(_next != 0) {
		_next->draw();
	}
}
