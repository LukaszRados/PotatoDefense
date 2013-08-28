#include "BaseLayer.hpp"

BaseLayer::BaseLayer(sf::RenderWindow *w):Layer(w) {


	Wall *wall = new Wall;

	for(int i = 0; i < Board::width; ++i) {
		Board::board[0][i] = wall;
		Board::board[Board::height - 1][i] = wall;
	}

	for(int i = 0; i < Board::height; ++i) {
		Board::board[i][0] = wall;
		Board::board[i][Board::width - 1] = wall;
	}

	for(int i = 14; i < Board::width - 1; ++i) {
		for(int j = 1; j < Board::height - 1; ++j) {
			Board::board[j][i] = wall;
		}
	}

	Board::board[7][0] = new Wall(2);
	Board::board[7][14] = new Wall(3);

	_next = new TowerLayer(w);
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

	}
}

void BaseLayer::draw() {
	if(_next != 0) {
		_next->draw();
	}
}

void BaseLayer::update(){
	if(_next != 0 )
		_next->update();
}
