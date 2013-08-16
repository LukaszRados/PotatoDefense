#ifndef DIALOGLAYER_HPP_
#define DIALOGLAYER_HPP_


#include "Layer.hpp"
#include "TowerLayer.hpp"
#include <iostream>

/**
 * Klasa DialogLayer rysuje wszystkie okienka dialogowe,
 * czyli to, co ma byc wyswietlone po pierwszym kliknieciu
 */

class DialogLayer : public Layer {
public:
	DialogLayer(sf::RenderWindow *w);
	virtual ~DialogLayer();
	virtual void parseEvent(sf::Event &event);
	virtual void draw();
};

#endif /* DIALOGLAYER_HPP_ */
