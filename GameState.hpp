#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "PausableClock.hpp"
/**
 * \enum Typ wyliczeniowy opisujacy stan, w jakim znajduje sie aplikacja
 */


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

/**
 *  \class GameState
 *  \brief Kontener na zmienne globalne
 *
 *  Klasa statyczna GameState, ktora zastepuje zmienne globalne i zbiera je w jednym miejscu.
 */

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
	/**
	 * Procedura ktora przywraca stan poczatkowy klasie GameState.
	 */
	static void reset();
	/**
	 * Procedura zatrzymujaca wszystkie zegary w klasie GameState.
	 */
	static void pause();
	/**
	 * Procedura wznawiajaca prace wszystkich zegarow w klasie GameState.
	 */
	static void unpause();
	/**
	 * Procedura inicjujaca klase GameState, w tym wczytanie testur, czcionek i dzwiekow.
	 */
	static void init();
	/**
	 * Procedura czyszczaca, odpowiednik statycznego "destruktora".
	 */
	static void deinit();

	static void toggleMusic();
};

#endif /* GAMESTATE_HPP_ */
