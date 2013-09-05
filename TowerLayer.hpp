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

/**
 * \class TowerLayer
 * \brief Warstwa obslugujaca wiezyczki
 *
 * W tej warstwie dzieje sie najwiecej magii. W funkcji parseEvent obslugiwane sa zdarzenia, co pozwala na budowanie, ulepszanie i sprzedawanie wiez.
 * Natomiast w funkcja update zajmuje sie strzelaniem wiez. Warstwa ta bardzo mocno wspolpracuje z warstwa WormLayer, ktora jest nastepna na stosie.
 * Po kazdej zmianie w planszy(kupienie lub sprzedaz wiezy) jest ona o tym informowana.
 */
class TowerLayer : public Layer {
public:
	/**
	 * Konstruktor. To w nim stan gry jest faktycznie wczytywany - w tym miejscu z pliku zapisu wczytywane sa wieze oraz dane klasy GameState(pieniadze, pozostale szanse, czas,..)
	 */
	TowerLayer(sf::RenderWindow *w,std::string);

	virtual ~TowerLayer();
	/**
	 * Procedura do obslugi zdarzen.
	 */
	virtual void parseEvent(sf::Event &event);
	/**
	 * Procedura do rysowania warstwy.
	 */
	virtual void draw();
	/**
	 * Procedura aktualizujaca logike warstwy - przemieszczanie sie robali, strzelanie wiez...
	 */
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
