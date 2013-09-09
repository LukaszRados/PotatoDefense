#ifndef WALL_HPP_
#define WALL_HPP_

#include "Clickable.hpp"
#include <SFML/Graphics.hpp>

/**
 * \class Wall
 * \brief Klasa sluzaca do stworzenia ramki dookola planszy. W skrocie jest to wieza ktora nie strzela.
 */
class Wall : public Clickable {
public:
	/**
	 * Konstruktor domyslny, rownowazny z Wall(1)
	 */
	Wall();
	/**
	 * Konstruktor okreslajacy rodzaj muru
	 * \param n rodzaj muru ( 1 -mur, 2 - wejscie dla robali, 3 - wyjscie)
	 */
	Wall(int n);
	/**
	 * Wirtualny destruktor
	 */
	virtual ~Wall();
	/**
	 * Nadpisana funkcja getName z klasy Clickable
	 */
	virtual std::string getName() const;
	/**
	 * Procedura zwracajaca rodzaj muru
	 */
	virtual int getNumber() const;

private:
	int _number;
};


#endif /* WALL_HPP_ */
