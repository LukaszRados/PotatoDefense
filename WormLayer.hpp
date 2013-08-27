#ifndef WORMLAYER_HPP_
#define WORMLAYER_HPP_

#include "Layer.hpp"
#include "BgLayer.hpp"
#include "Worm.hpp"
#include <list>


/**
 * Warstwa do obslugi robakow. Szuka im sciezki, animuje je oraz decyduje kiedy wchodza nastepne
 */

class WormLayer : public Layer {
public:
	WormLayer(sf::RenderWindow *w);
	virtual ~WormLayer();
	virtual void parseEvent(sf::Event &event);
	virtual void draw();
	void setPath(std::vector<std::vector<int> >);

	bool pathExists(std::vector<std::vector<int> >);
	// wg tej sciezki beda chodzic robaki
	static std::vector<std::vector<int> > _path;
	static std::list<Worm> worms;
private:
	const int _dens=3; // stala okresla gestosc siatki po ktorej chodza stonki
	// Board::height okresla rozmiar planszy
	const int _s = Board::height; //s jak size


	sf::Clock _time;
	static bool move(Worm &, int);







	// metoda do przerabiania siatki wiez na siatke robakow - niepotrzebna
	//std::vector<std::vector<int> > getBoard(std::vector<std::vector<int> >);
	//std::vector<std::vector<int> > _board;

	std::vector<std::vector<int> >  findPath(std::vector<std::vector<int> >);

	/**
	 * wypisuje dowolna tablice dwuwymiarowa, endl co wiersz
	 */
	void printPath(std::vector<std::vector<int> >);
	/** Wypelnia tablice _board o gestszej siatce wartosciami val w polach x,y(w zasiegu _dens)
	 *
	 */
//	niepotrzebne
//	void fillBoard(std::vector<std::vector<int> >  & board,int val, int x, int y);

};


#endif
