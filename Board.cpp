#include "Board.hpp"

std::vector<std::vector<Clickable*>> Board::board;
sf::RenderWindow* Board::window;
Clickable* Board::buffer;
int Board::width;
int Board::height;
int Board::fieldW;
int Board::fieldH;

void Board::init() {
	width = 20;
	height = 15;

	fieldW = 40;
	fieldH = 40;

	window = new sf::RenderWindow(sf::VideoMode(width * fieldW, height * fieldH), "Potato Defense"); // sf::Style::Fullscreen
	buffer = 0;

	for(int i = 0; i < Board::height; ++i) {
		Board::board.push_back(std::vector<Clickable*>(Board::width, NULL));
	}
}

void Board::deinit() {
//	for(int i = 0; i < Board::height; ++i) {
//		for(int j = 0; j < Board::width; ++j) {
//			if(Board::board[i][j] != 0) {
//				delete Board::board[i][j];
//			}
//		}
//	}

//	if(Board::buffer != 0) {
//		delete Board::buffer;
//	}

	if(Board::window != 0) {
		delete Board::window;
	}
}
