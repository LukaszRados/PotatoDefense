#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Clickable.hpp"

class Board {
public:
	static void init();
	static void deinit();
	static std::vector<std::vector<int>> getBoardAsInts();

	static std::vector<std::vector<Clickable*>> board;
	static sf::RenderWindow* window;
	static Clickable* buffer;
	static int width;
	static int height;
	static int fieldW;
	static int fieldH;
};

#endif /* BOARD_HPP_ */
