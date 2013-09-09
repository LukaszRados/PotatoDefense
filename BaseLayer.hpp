#ifndef BASELAYER_HPP_
#define BASELAYER_HPP_

#include "Layer.hpp"
#include "BgLayer.hpp"
#include "Wall.hpp"
#include <string>

/**
 * \class BaseLayer
 * \brief Klasa warstwy-bazy dla kolejnych.
 *
 * Klasa BaseLayer nie zajmuje sie rysowaniem, dopelnia ona inicjalizacje klas Board i GameState. Pozwala to na wielokrotne rozpoczynanie gry podczas jednego uruchomienia programu.
 */

class BaseLayer : public Layer {
public:
	/**
	 * Konstruktor
	 * \param w Wskaznik do sf::RenderWindow, na ktorym obiekt ma rysowac.
	 * \param filename Nazwa pliku z zapisem (w przypadku wczytywania stanu gry).
	 */
	BaseLayer(sf::RenderWindow *w, std::string filename="");
	/**
	 * Wirtualny destruktor
	 */
	virtual ~BaseLayer();
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

};


#endif /* BASELAYER_HPP_ */
