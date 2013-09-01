#include "GameState.hpp"

int GameState::lifes;
int GameState::money;
int GameState::wave;
std::string GameState::info;

/**
 * Map of all used textures
 */
std::map<std::string, sf::Texture*> GameState::textures = std::map<std::string, sf::Texture*>();

sf::Clock GameState::globalTime;
sf::Clock GameState::waveTime;

States GameState::state = MainMenu;

void GameState::reset() {
	lifes = 1;
	money = 10000;
	wave = 1;
	info = "";
}
