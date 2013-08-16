#include "BaseLayer.hpp"

BaseLayer::BaseLayer(sf::RenderWindow *w):Layer(w) {
	_next = new DialogLayer(w);

	_active = sf::RectangleShape(sf::Vector2f(40, 40));
	_active.setOutlineColor(sf::Color(255, 255, 255, 100));
	_active.setOutlineThickness(1);
	_active.setFillColor(sf::Color::Transparent);

	Wall *wall = new Wall;

	for(int i = 0; i < Board::width; ++i) {
		Board::board[0][i] = wall;
		Board::board[Board::height - 1][i] = wall;
	}

	for(int i = 0; i < Board::height; ++i) {
		Board::board[i][0] = wall;
		Board::board[i][Board::width - 1] = wall;
	}

	_toDraw.push_back(wall);
}

BaseLayer::~BaseLayer() {

}

void BaseLayer::parseEvent(sf::Event &event) {
	if(_next != 0) {
		_next->parseEvent(event);
	}

	switch(event.type) {
	case sf::Event::Closed:
		_window->close();
		break;

	case sf::Event::KeyPressed:
		if(event.key.code == sf::Keyboard::Escape) {
			_window->close();
		}
		break;

	case sf::Event::MouseMoved:
			int x = event.mouseMove.x / 40;
			int y = event.mouseMove.y / 40;

			_active.setPosition(x * 40, y * 40);

			break;
	}
}

void BaseLayer::draw() {
	if(_next != 0) {
		_next->draw();
	}

	_window->draw(_active);
}
