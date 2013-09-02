#include <SFML/Graphics.hpp>
#include <iostream>				// for debugging

#include "GameState.hpp"
#include "Layer.hpp"
#include "MenuLayer.hpp"

int main() {
	Board::init();
	Layer *layer = new MenuLayer(Board::window);
	GameState::init();

	while(Board::window->isOpen()) {
		Board::window->clear();

		sf::Event event;

		while(Board::window->pollEvent(event)) {
			layer->parseEvent(event);
		}

		layer->draw();
		layer->update();
		Board::window->display();
	}

	delete layer;
	Board::deinit();
	GameState::deinit();

    return 0;
}
