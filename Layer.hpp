#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "TowerBuilder.hpp"
#include "Board.hpp"

class Layer {
public:
	Layer(sf::RenderWindow *w);
	virtual ~Layer();
	virtual void parseEvent(sf::Event &event);
	virtual void draw();

protected:
	Layer* _next = 0;
	sf::RenderWindow *_window = 0;
	std::vector<Clickable*> _toDraw;
};


#endif /* LAYER_HPP_ */
