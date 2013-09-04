#include "Board.hpp"

/**
 * Board - contains towers, tower builders, entrance and exit (pointers)
 */
std::vector<std::vector<Clickable*>> Board::board;
/**
 * Pointer to rendered window
 */
sf::RenderWindow* Board::window;

/**
 * Buffer - keeps pointer to Clickable that is currently called
 */
Clickable* Board::buffer;

/**
 * width, height - number of fields (x, y)
 */
int Board::width;
int Board::height;

/**
 * fieldW, fieldH - size of single field (in px)
 */
int Board::fieldW;
int Board::fieldH;

/**
 * Prepares Board before game:
 * 		- Sets size of board and single field
 * 		- Creates new window
 * 		- Clear array of arrays of Clickable ;)
 */
void Board::init() {
	width = 20;
	height = 15;

	fieldW = 40;
	fieldH = 40;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window = new sf::RenderWindow(sf::VideoMode(width * fieldW, height * fieldH), "Potato Defense", sf::Style::Default, settings); // sf::Style::Fullscreen

	sf::Image icon;
	icon.loadFromFile("graphics/icon.png");

	window->setIcon(32, 32, icon.getPixelsPtr());
	window->setTitle("Potato Defense");
	buffer = 0;

	for(int i = 0; i < Board::height; ++i) {
		Board::board.push_back(std::vector<Clickable*>(Board::width, NULL));
	}
}

/**
 * Clear memory after game
 */
void Board::deinit() {
	if(Board::window != 0) {
		delete Board::window;
	}

}

/**
 * Returns board as array of ints
 * Useful for worms to allow them to get directions
 */
std::vector<std::vector<int>> Board::getBoardAsInts() {
	std::vector<std::vector<int>> tmp;

	for(unsigned int i = 0; i < Board::board.size(); ++i) {
		tmp.push_back(std::vector<int>());

		for(unsigned int j = 0; j < Board::board[i].size(); ++j) {
			if(!Board::board[i][j]) tmp[i].push_back(0);
			else if(Board::board[i][j]->getName() == "wall") tmp[i].push_back(((Wall*)Board::board[i][j])->getNumber());
			else tmp[i].push_back(1);
		}
	}

	return tmp;
}

void Board::save(){
	std::cout << "Board::save " << std::endl;
	std::ofstream file;
	file.open("autosave.pd", std::ofstream::binary);
	if(!file){
		std::cout << "Autosave could not be created!" << std::endl;
	} else {
		file << GameState::money << " " << GameState::lifes << " " << GameState::wave << " ";
		file << GameState::globalTime.getElapsedTime().asSeconds() << " ";


		for(int y=0;y<Board::height;y++)
			for(int x=0;x<Board::height;x++){
				if(Board::board[y][x]!=nullptr && Board::board[y][x]->getName()=="tower"){
					Board::board[y][x]->save(file);
					file <<" ";
				}
			}

		file.close();
	}
}
