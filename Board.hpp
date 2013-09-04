#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Clickable.hpp"
#include "Wall.hpp"
#include "GameState.hpp"


class Board {
public:
	static void init();
	static void deinit();
	static std::vector<std::vector<int>>  getBoardAsInts();

	static std::vector<std::vector<Clickable*>> board;
	static sf::RenderWindow* window;
	static Clickable* buffer;
	static int width;
	static int height;
	static int fieldW;
	static int fieldH;
	static void save();
};

#endif /* BOARD_HPP_ */
