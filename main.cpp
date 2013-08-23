#include <SFML/Graphics.hpp>
#include <iostream>				// for debugging

#include "GameState.hpp"
#include "Layer.hpp"
#include "BaseLayer.hpp"

int main() {
	Board::init();
	Layer *layer = new BaseLayer(Board::window);

	/**
	 * Showcase of getBoardAsInts() result
	*/
//	auto b = Board::getBoardAsInts();
//	for(auto i : b) {
//		for(auto j : i) {
//			std::cout << j << " ";
//		}
//		std::cout << std::endl;
//	}
/*
	 * End of showcase.
	 */

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
