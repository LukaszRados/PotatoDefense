#ifndef BGLAYER_HPP_
#define BGLAYER_HPP_

#include "Layer.hpp"
#include "ToString.hpp"

class BgLayer : public Layer {
public:
	BgLayer(sf::RenderWindow *w);
	virtual void parseEvent(sf::Event &event);
	virtual void draw();
};

#endif /* BGLAYER_HPP_ */
