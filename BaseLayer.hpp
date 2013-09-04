#ifndef BASELAYER_HPP_
#define BASELAYER_HPP_

#include "Layer.hpp"
#include "BgLayer.hpp"
#include "Wall.hpp"
#include <iostream>
#include <string>

/**
 * Klasa BaseLayer nie zajmuje sie rysowaniem,
 * jej zadaniem jest jedynie obsluzenie zamykanie okna
 */

class BaseLayer : public Layer {
public:
	BaseLayer(sf::RenderWindow *w, std::string="");
	virtual ~BaseLayer();
	virtual void parseEvent(sf::Event &event);
	virtual void draw();
	virtual void update();
private:

};


#endif /* BASELAYER_HPP_ */
