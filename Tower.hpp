#ifndef TOWER_HPP_
#define TOWER_HPP_

#include "Clickable.hpp"
#include "ToString.hpp"
#include "Worm.hpp"
#include "PausableClock.hpp"

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>


/**
 * \brief Klasa wiezy
 *
 * Obiekty tej klasy reprezntuja wieze. Klasa dziedziczy po Clickable, wiec mozna w nia klikac, co powoduje pojawienie sie dialogu (to jest obsluzone w TowerLayer). Kazda wieza to
 * autonomiczny obiekt, ktory strzela do robali we wlasnym tempie dzieki wewnetrznemu zegarowi. W tej klasie zastosowano macie 3-wymiarowa, ktora zawiera wszystkie statystyki dla wiezy:
 * [rodzaj wiezy][poziom][wlasciowsc wiezy]. Pozwolilo to na wygodne balansowanie rozgrywki oraz na latwe wczytywanie i zapisywanie stanu gry, dzieki metodzie setStats(rodzaj, poziom).
 * </br></br>
 * Dla wygody ma przyjazn z klasa TowerLayer.
 */
class Tower : public Clickable {
public:
	/**
	 * Konstruktor domyslny. Rownowazny z Tower(0)
	 */
	Tower();
	/**
	 * Konstruktor okreslajacy rodzaj wiezy i ustawiajacy odpowiednie statystyki
	 */
	Tower(int);
	/**
	 * Wirtualny destruktor
	 */
	virtual ~Tower();
	/**
	 * Funkcja strzelania. Zadaje wybranemu przez siebie robakowi z listy (oczywiscie jesli jest jakis w zasiegu i moze strzelac do danego rodzaju robaka) obrazenia zgodne ze statystykami
	 * \param enemies Lista robakow na planszy
	 */
	virtual void shoot(std::list<Worm> & enemies);
	/**
	 * Przeciazona funkcja z klasy Clickable
	 */
	virtual std::string getName() const;
	/**
	 * Funkcja zapisu wiezy do strumienia
	 */
	virtual void save(std::ostream &) const;
	/**
	 * Funkcja wczytywania wiezy ze strumienia
	 */
	virtual bool load(std::istream &);
	int getLevel() const;
	int getNumber() const;
	int getRange() const;
	int getRange(int) const;
	void levelUp();
	/**
	 * Funkcja zwracajaca pozycje w ukladzie wspolrzednych ekranu
	 */
	sf::Vector2f getPosition();
	/**
	 * Przeciazona funkcja z klasy Clickable
	 */
	virtual std::string getDesc(int) const;
	/**
	 * Macierz statystyk
	 */
	static int  _stats[3][3][5];
	/**
	 * Macierz opisow
	 */
	static std::string _desc[3][3];

	friend class TowerLayer;
protected:
	int _level = 1;
	int _no;
	int _range;
	int _damage;
	int _reloadTime;
	PausableClock _time;
	bool _firstShot;
	Worm * _target;
	int _antiAir;
	void setStats(int,int);
	sf::Sound _sound;
};


#endif /* TOWER_HPP_ */
