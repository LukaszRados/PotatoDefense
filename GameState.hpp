#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "PausableClock.hpp"

enum States {
	MainMenu	= 0,
	Game		= 1,
	Paused		= 2,
	GameOver	= 3,
	HowToPlay	= 4,
	Exit		= 5
};

struct GameState {
	static int lifes;
	static int money;
	static int wave;
	static std::string info;
	static std::map<std::string, sf::Texture*> textures;
	static std::map<std::string, sf::Music*> sounds;
	static PausableClock globalTime;
	static PausableClock waveTime;
	static States state;

	static void reset();
	static void pause();
	static void unpause();
};

#endif /* GAMESTATE_HPP_ */
