#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "TowerBuilder.hpp"
#include "Board.hpp"

/**
 * \class Layer
 * \brief Klasa podstawowa dla kazdej warstwy gry.
 *
 * Po klasie Layer dziedzicza wszystkie inne warstwy. Kazda warstwa zawiera wskaznik _next do kolejnej warstwy, dzieki czemu tworza one stos. <br>
 * Kazda warstwa rysuje siebie i wywoluje procedure draw() nastepnej. Tak samo dzialaja procedury parseEvent()(do obslugi zdarzen zaimplementowanyc w bibliotece SFML) oraz update()(do obliczania logiki warstwy).
 *
 */
class Layer {
public:
	/**
	 * Konstruktor warstwy.
	 * \param sf::RenderWindow * - wskaznik do obiektu obslugujacego rysowanie na ekranie.
	 */
	Layer(sf::RenderWindow *w);
	/**
	 * Wirtualny detruktor.
	 */
	virtual ~Layer();
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
protected:
	Layer* _next = 0;
	sf::RenderWindow *_window = 0;
	std::vector<Clickable*> _toDraw;
};


#endif /* LAYER_HPP_ */
