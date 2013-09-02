#include "GameState.hpp"

int GameState::lifes;
int GameState::money;
int GameState::wave;
std::string GameState::info;

/**
 * Map of all used textures
 */
std::map<std::string, sf::Texture*> GameState::textures = std::map<std::string, sf::Texture*>();
/** And music */
std::map<std::string, sf::Music*> GameState::sounds = std::map<std::string, sf::Music*>();

PausableClock GameState::globalTime;
PausableClock GameState::waveTime;

States GameState::state = MainMenu;

void GameState::reset() {
	lifes = 1;
	money = 10000;
	wave = 1;
	info = "";
}

void GameState::pause(){
	GameState::globalTime.pause();
	GameState::waveTime.pause();
}

void GameState::unpause(){
	if(GameState::globalTime.isPaused())
		GameState::globalTime.start();
	if(GameState::waveTime.isPaused())
		GameState::waveTime.start();
}
