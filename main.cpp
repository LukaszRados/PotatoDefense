#include <SFML/Graphics.hpp>
#include <iostream>				// for debugging

#include "GameState.hpp"
#include "Layer.hpp"
#include "BaseLayer.hpp"

int main() {
	Board::init();
	Layer *layer = new BaseLayer(Board::window);

	while(Board::window->isOpen()) {
		Board::window->clear();

		sf::Event event;

		while(Board::window->pollEvent(event)) {
			layer->parseEvent(event);
		}

		layer->draw();
		Board::window->setTitle("Potato Defense");
		Board::window->display();
	}

	Board::deinit();

    return 0;
}
