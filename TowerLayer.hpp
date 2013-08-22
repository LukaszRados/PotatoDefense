#ifndef TOWERLAYER_HPP_
#define TOWERLAYER_HPP_

#include "Layer.hpp"
#include "TowerBuilder.hpp"
#include "Tower.hpp"
#include "Dialog.hpp"
#include "WormLayer.hpp"
#include "ToString.hpp"

#include <iostream>

class TowerLayer : public Layer {
public:
	TowerLayer(sf::RenderWindow *w);
	virtual void parseEvent(sf::Event &event);
	virtual void draw();

private:
	std::vector<TowerBuilder*> _builders;
	Dialog* _dialog = 0;
	sf::RectangleShape _active;
};


#endif /* TOWERLAYER_HPP_ */
