#ifndef CLICKABLE_HPP_
#define CLICKABLE_HPP_

#include <SFML/Graphics.hpp>
#include <string>
/**
 * \class Clickable
 * \brief Abstrakcyjna klasa baza dla elemntow interfejsu ktore mozna kliknac
 *
 * Klasa zapewnia interfejs dla elemntow, ktore mozna kliknac. Posiada ona zestaw metod wirtualnych:
 */
class Clickable {
public:
	/**
	 * Domyslny konstruktor
	 */
	Clickable();
	/**
	 * Wirtualny destruktor
	 */
	virtual ~Clickable();
	/**
	 * Procedura ustawiajaca skladnik X
	 */
	virtual void setX(int);
	/**
	 * Procedura ustawiajaca skladnik Y
	 */
	virtual void setY(int);
	/**
	 * Procedura zwracajaca skladnik X
	 */
	virtual int getX() const;
	/**
	 * Procedura zwracajaca skladnik Y
	 */
	virtual int getY() const;
	/**
	 * Procedura zwracajaca skladnik sprite
	 */
	virtual sf::IntRect getSprite() const;
	/**
	 * Procedura zwracajaca nazwe typu: wieza, mur...
	 */
	virtual std::string getName() const = 0;
	/**
	 * Procedura zwracajaca opis obiektu
	 */
	virtual std::string getDesc() const;
	/**
	 * Procedura pozwalajaca zapisac do strumienia stan obiektu
	 */
	virtual void save(std::ostream &) const;
	/**
	 * Procedura wczytywania ze strumienia stanu obiektu
	 */
	virtual bool load(std::istream &);
protected:
	unsigned int _x = 0;
	unsigned int _y = 0;
	sf::IntRect _sprite;
	std::string _desc = "";

};


#endif /* CLICKABLE_HPP_ */
