#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "PausableClock.hpp"

enum States {
	MainMenu	= 0,
	Game		= 1,
	Paused		= 2,
	GameOver	= 3,
	Win			= 4,
	HowToPlay	= 5,
	Load		= 6,
	Exit		= 7
};

struct GameState {
	static int lifes;
	static int money;
	static int wave;
	static const int maxWaves;
	static const int secondsBetweenWaves;
	static std::string info;
	static std::map<std::string, sf::Texture*> textures;
	static std::map<std::string, sf::Music*> sounds;
	static std::map<std::string, sf::Font*> fonts;
	static PausableClock globalTime;
	static sf::Time loadedTime;
	static PausableClock waveTime;
	static States state;
	static bool music;

	static void reset();
	static void pause();
	static void unpause();
	static void init();
	static void deinit();

	static void toggleMusic();
};

#endif /* GAMESTATE_HPP_ */
