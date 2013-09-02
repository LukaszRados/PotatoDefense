#ifndef MENULAYER_HPP_
#define MENULAYER_HPP_

#include "Layer.hpp"
#include "BaseLayer.hpp"
#include "ToString.hpp"
#include "GameState.hpp"

#include <iostream>

class MenuLayer : public Layer {
public:
	MenuLayer(sf::RenderWindow*);
	~MenuLayer();

	virtual void draw();
	virtual void parseEvent(sf::Event&);
	virtual void update();

private:
	struct MenuPosition {
		int no;			// ID
		int state;		// enabled / disabled
		bool active;	// hover
		States onClick;	// state changed on click
	};

	MenuPosition _menu[4] = {
		{0, 0, false, States::MainMenu},
		{1, 1, false, States::Game},
		{2, 1, false, States::HowToPlay},
		{3, 1, false, States::Exit}
	};

	sf::Sprite _sprite = sf::Sprite();
};

#endif /* MENULAYER_HPP_ */
