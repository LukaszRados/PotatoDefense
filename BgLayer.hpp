#ifndef BGLAYER_HPP_
#define BGLAYER_HPP_

#include "Layer.hpp"
#include "ToString.hpp"
#include "TowerLayer.hpp"

class BgLayer : public Layer {
public:
	BgLayer(sf::RenderWindow *w);
	virtual ~BgLayer();
	virtual void parseEvent(sf::Event &event);
	virtual void draw();
	virtual void update();
};

#endif /* BGLAYER_HPP_ */
