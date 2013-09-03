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

const int GameState::maxWaves=2;
const int GameState::secondsBetweenWaves=5;

bool GameState::music = true;

void GameState::reset() {
	lifes = 20;
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

void GameState::toggleMusic() {
	GameState::music = !GameState::music;
	if(GameState::music) {
		GameState::sounds["forest"]->play();
	}
	else {
		GameState::sounds["forest"]->stop();
	}
}

void GameState::init() {
	textures["bugs"] = new sf::Texture();
	textures["bugs"]->loadFromFile("graphics/worms.png");

	textures["nextIn"] = new sf::Texture();
	textures["nextIn"]->loadFromFile("graphics/nextIn.png");

	textures["nextNo"] = new sf::Texture();
	textures["nextNo"]->loadFromFile("graphics/nextNo.png");

	textures["towers"] = new sf::Texture();
	textures["towers"]->loadFromFile("graphics/towers.png");

	textures["dialog"] = new sf::Texture();
	textures["dialog"]->loadFromFile("graphics/dialog.png");

	textures["splash"] = new sf::Texture();
	textures["splash"]->loadFromFile("graphics/splash.png");

	textures["menu"] = new sf::Texture();
	textures["menu"]->loadFromFile("graphics/menu.png");

	textures["pause"] = new sf::Texture();
	textures["pause"]->loadFromFile("graphics/pause.png");

	textures["gameover"] = new sf::Texture();
	textures["gameover"]->loadFromFile("graphics/gameover.png");

	textures["victory"] = new sf::Texture();
	textures["victory"]->loadFromFile("graphics/victory.png");

	textures["howToPlay"] = new sf::Texture();
	textures["howToPlay"]->loadFromFile("graphics/howToPlay.png");

	textures["volume"] = new sf::Texture();
	textures["volume"]->loadFromFile("graphics/volume.png");

	textures["bg"] = new sf::Texture();
	textures["bg"]->loadFromFile("graphics/bg.png");

	textures["panel"] = new sf::Texture();
	textures["panel"]->loadFromFile("graphics/panel.png");

	sounds["menu"] = new sf::Music();
	sounds["menu"]->openFromFile("music/menu.ogg");

	sounds["gong"] = new sf::Music();
	sounds["gong"]->openFromFile("music/gong.ogg");

	sounds["forest"] = new sf::Music();
	sounds["forest"]->openFromFile("music/forest.ogg");
}

void GameState::deinit() {
//	for(auto & i : textures) {
//		if(i.second != nullptr) {
//			delete i.second;
//			i.second = 0;
//		}
//	}

//	for(auto & i : sounds){
//		if(i.second != nullptr){
//			delete i.second;
//			i.second=nullptr;
//		}
//	}
}
