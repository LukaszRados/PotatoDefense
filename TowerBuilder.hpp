#ifndef TOWERBUILDER_HPP_
#define TOWERBUILDER_HPP_

#include "Clickable.hpp"
#include "Tower.hpp"
#include <SFML/Graphics.hpp>

/**
 * \class TowerBuilder
 * \brief Klasa odpowiedzialna za mozliwosc budowania wiezyczek.
 *
 * Dany TowerBuilder umozliwia tworzenie wiezyczek tylko jednego rodzaju.
 * Udostepnia ponadto informacje o koszcie ich wybudowania i koszcie sprzedazy.
 */

class TowerBuilder : public Clickable {
public:
	/**
	 * Konstruktor domyslny - ustawi numer wiezyczki na 0
	 */
	TowerBuilder();
	/**
	 * Konstruktor pozwalajacy na wybranie budowanej wiezyczki
	 */
	TowerBuilder(int);
	virtual ~TowerBuilder();
	/**
	 * Funkcja secondClick pozwala postawic wiezyczke na polu, ktore zostalo klikniete
	 * Jezeli nie ma dostatecznej ilosci srodkow lub pole jest zajete (przez inna wiezyczke lub robaki)
	 * to nowa wieza nie zostanie postawiona.
	 * Funkcja wywolywana jest dopiero po uprzednim kliknieciu na TowerBuilder w prawym panelu
	 * \return Clickable*
	 */
	Clickable* secondClick(int, int);
	/**
	 * Zwraca koszt wybudowania wiezyczki na danym poziomie
	 * \param lvl Poziom, na ktorym chcemy zbudowac wiezyczke
	 * \return int Koszt wybudowania
	 */
	int getCost(int lvl) const;
	/**
	 * Zwraca ilosc pieniedzy, ktore otrzyma gracz sprzedajac wiezyczke
	 * Ilosc ta to suma kosztow zbudowania wiezyczki na wszystkich dotychczasowych poziomach
	 * pomniejszona o 20%
	 * \param lvl Poziom, na ktorym jest wiezyczka
	 * \return int Zysk ze sprzedazy
	 */
	int getSellingCost(int lvl) const;
	/**
	 * Funkcja wirtualna identyfikujaca obiekty tej klasy
	 * \return std::string("towerBuilder")
	 */
	virtual std::string getName() const;
	/**
	 * Funkcja wirtualna zwracajaca opis budowniczego
	 * Opis zawiera koszt wzniesienia wiezyczki, jej krotki opis oraz parametry
	 * \return std::string Opis wiezyczki na 1 poziomie
	 */
	virtual std::string getDesc() const;
	/**
	 * Funkcja pomocnicza dajaca dostep do _towerNumer
	 * \return int Rodzaj wiezyczki
	 */
	int getTowerNumber() const;

protected:
	int _towerNumber = 0;
};


#endif /* TOWERBUILDER_HPP_ */
