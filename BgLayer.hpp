#ifndef BGLAYER_HPP_
#define BGLAYER_HPP_

#include "Layer.hpp"
#include "ToString.hpp"
#include "TowerLayer.hpp"
/**
 * \class BgLayer
 * \brief Klasa odpowiedzialna za tlo
 *
 * Klasa ta rysuje tlo, informacje na pasku bocznym oraz czas.
 */
class BgLayer : public Layer {
public:
	/**
	 * Konstruktor
	 * \param w Wskaznik do sf::RenderWindow, na ktorym obiekt ma rysowac.
	 * \param filename Nazwa pliku z zapisem (w przypadku wczytywania stanu gry).
	 */
	BgLayer(sf::RenderWindow *w, std::string filename="");
	/**
	 * Wirtualny destruktor
	 */
	virtual ~BgLayer();
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
};

#endif /* BGLAYER_HPP_ */
