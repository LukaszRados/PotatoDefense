#include "BaseLayer.hpp"

BaseLayer::BaseLayer(sf::RenderWindow *w, std::string filename):Layer(w) {
	Wall *wall = new Wall;
	GameState::reset();

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

	_next = new BgLayer(w,filename);
	_toDraw.push_back(wall);
}

BaseLayer::~BaseLayer() {
	if(_next != 0) {
		delete _next;
	}
}

void BaseLayer::parseEvent(sf::Event &event) {
	if(_next != 0) {
		_next->parseEvent(event);
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
