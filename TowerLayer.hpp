#ifndef TOWERLAYER_HPP_
#define TOWERLAYER_HPP_

#include "Layer.hpp"
#include "TowerBuilder.hpp"
#include "Tower.hpp"
#include "Dialog.hpp"
#include "BgLayer.hpp"
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
};


#endif /* TOWERLAYER_HPP_ */
