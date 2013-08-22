#ifndef WORMLAYER_HPP_
#define WORMLAYER_HPP_

#include "Layer.hpp"
#include "BgLayer.hpp"


/**
 * Warstwa do obslugi robakow. Szuka im sciezki, animuje je oraz decyduje kiedy wchodza nastepne
 */

class WormLayer : public Layer {
public:
	WormLayer(sf::RenderWindow *w);
	virtual ~WormLayer();
	virtual void parseEvent(sf::Event &event);
	virtual void draw();
	void getBoard(std::vector<std::vector<int> >  ints);
private:
	const int _dens=3; // stala okresla gestosc siatki po ktorej chodza stonki
	// Board::height okresla rozmiar planszy
	const int _s = Board::height; //s jak size

	std::vector<std::vector<int> > _board;
	void printBoard();
	/** Wypelnia tablice _board o gestszej siatce wartosciami val w polach x,y(w zasiegu _dens)
	 *
	 */
	void fillBoard(int val, int x, int y);

};


#endif
