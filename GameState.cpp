#include "GameState.hpp"

int GameState::lifes = 20;
int GameState::money = 1000;
int GameState::wave = 1;
std::string GameState::info = "[ESC] Exit";

/**
 * Map of all used textures
 */
std::map<std::string, sf::Texture*> GameState::textures = std::map<std::string, sf::Texture*>();

sf::Clock GameState::globalTime;
