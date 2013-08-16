#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

struct GameState {
	static int lifes;
	static int money;
	static int wave;
	static std::string info;
	static std::map<std::string, sf::Texture*> textures;
};

#endif /* GAMESTATE_HPP_ */
