#ifndef WORMLAYER_HPP_
#define WORMLAYER_HPP_

#include "Layer.hpp"
#include "Worm.hpp"
#include "PausableClock.hpp"
#include "Board.hpp"
#include <list>
#include <vector>
#include <cmath>

/**
 * \brief Warstwa do obslugi robakow.
 *
 * Szuka im sciezki, animuje je oraz decyduje kiedy wchodza nastepne. Mocno wspolpracuje z klasa TowerLayer oraz Board, dzieki ktorym jest w stanie wyznaczyc sciezke dla robali.
 * Udostepnia takze interfejs specjalnie dla klasy TowerLayer, mianowicie funkcje pathExists() oraz isFree(), ktore okreslaja gdzie moze stanac kolejna wieza, a gdzie nie.</br>
 * Zeby zapewnic, ze fale zawsze sa takie same, wykorzystano macierz enemies, gdzie pod indeksami [fala][czas] kryje sie rodzaj robaka ktory ma sie pojawic jako kolejny.
 *
 * </br></br> Dla wygody ma zadeklarowana przyjazn z klasa Worm.
 */

class WormLayer : public Layer {
public:
	/**
	 * Konstruktor
	 */
	WormLayer(sf::RenderWindow *w);
	/**
	 * Wirtualny destruktor
	 */
	virtual ~WormLayer();
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
	void setPath(std::vector<std::vector<int> >);
	bool pathExists(std::vector<std::vector<int> >);
	static std::vector<std::vector<int> > _path;
	static std::list<Worm> worms;
	static bool isFree(int, int);
	static std::vector<std::vector<int> > enemies;
private:
	int _s=Board::height;
	bool _moreEnemies; // okresla czy w danej fali pojawia sie kolejni przeciwnicy
	bool _waveOn; //okresla czy trwa fala
	PausableClock _time; // zegar do animowania robakow
	std::vector<std::vector<int> >  findPath(std::vector<std::vector<int> >);
	void printPath(std::vector<std::vector<int> >);
};


#endif
