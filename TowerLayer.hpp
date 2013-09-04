#ifndef TOWERLAYER_HPP_
#define TOWERLAYER_HPP_

#include "Layer.hpp"
#include "TowerBuilder.hpp"
#include "Tower.hpp"
#include "Dialog.hpp"
#include "WormLayer.hpp"
#include "ToString.hpp"
#include "GameState.hpp"
#include <cmath>

#include <iostream>

class TowerLayer : public Layer {
public:
	TowerLayer(sf::RenderWindow *w,std::string);
	virtual ~TowerLayer();
	virtual void parseEvent(sf::Event &event);
	virtual void draw();
	virtual void update();
private:
	std::vector<TowerBuilder*> _builders;
	std::list<Tower*> _towers;
	Dialog* _dialog = 0;
	sf::RectangleShape _active;
	sf::Sprite _shadow;
	std::vector<sf::CircleShape> _ranges;
};


#endif /* TOWERLAYER_HPP_ */
