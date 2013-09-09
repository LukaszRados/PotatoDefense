#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Layer.hpp"
#include "MenuLayer.hpp"

int main() {
	Board::init();
	GameState::init();
	Layer *layer = new MenuLayer(Board::window);

	while(Board::window->isOpen()) {
		Board::window->clear();

		sf::Event event;

		while(Board::window->pollEvent(event)) {
			layer->parseEvent(event);
		}

		layer->update();
		layer->draw();

		Board::window->display();
	}

	delete layer;
	Board::deinit();
	GameState::deinit();

    return 0;
}
