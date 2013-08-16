#include <SFML/Graphics.hpp>
#include <iostream>

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
		Board::window->setTitle(GameState::info);
		Board::window->display();
	}

	Board::deinit();
	//std::vector<Object> worms;

	//Object::setWorms(&worms);

	/**
	sf::Texture sprites;
	if(!sprites.loadFromFile("graphics/sprites.png")) {
		std::cout << "Error: Cannot load sprites.png!";
		return 1;
	}

	sf::Sprite sprite;
	sprite.setTexture(sprites);
	sprite.setTextureRect(sf::IntRect(200, 0, 100, 100));





	sf::RenderWindow window(sf::VideoMode(600,300), "Test");

	while(window.isOpen()) {
		window.clear();

		sf::Event event;

		while(window.pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}

		}

		window.draw(sprite);

		window.display();
	}



	//Board t;
	//t.game(); */

    return 0;
}
