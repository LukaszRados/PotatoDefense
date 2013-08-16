#ifndef BASELAYER_HPP_
#define BASELAYER_HPP_

#include "Layer.hpp"
#include "DialogLayer.hpp"
#include "Wall.hpp"
#include <iostream>

/**
 * Klasa BaseLayer nie zajmuje sie rysowaniem,
 * jej zadaniem jest jedynie obsluzenie zamykanie okna
 */

class BaseLayer : public Layer {
public:
	BaseLayer(sf::RenderWindow *w);
	virtual ~BaseLayer();
	virtual void parseEvent(sf::Event &event);
	virtual void draw();

private:
	sf::RectangleShape _active;
};


#endif /* BASELAYER_HPP_ */