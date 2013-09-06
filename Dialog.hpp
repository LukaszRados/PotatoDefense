#ifndef DIALOG_CPP_
#define DIALOG_CPP_

#include "Clickable.hpp"
/**
 * \class Dialog
 * \brief Klasa dialogu
 *
 * Klasa ta odpowiada za rysowanie i obsluge dialogow, ktore pojawiaja sie po kliknieciu na wieze. Posiada interfejs odziedziczony po klasie Clickable.
 */
class Dialog : public Clickable {
public:
	/**
	 * Konstruktor okreslajacy rodzaj dialogu
	 * \param opt Okresla czy opcja Upgrade ma byc dostepna
	 * \param x Okresla polozenie dialogu
	 * \param y Okresla polozenie dialogu
	 */
	Dialog(bool opt, int x, int y);
	/**
	 * Procedura zwracajaca wartosc skladnika options, ktory okresla czy opcja Upgrade ma byc dostepna
	 */
	bool getOptions() const;
	/**
	 * Procedura ustawiajaca skladnik options
	 */
	void setOptions(bool);
	/**
	 * Funkcja wirtualna identyfikujaca obiekty tej klasy
	 * \return std::string("dialog")
	 */
	virtual std::string getName() const;
private:
	bool _options;
};

#endif /* DIALOG_CPP_ */
