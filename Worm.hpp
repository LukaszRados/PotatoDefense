#ifndef WORM_HPP_
#define WORM_HPP_

#include "Board.hpp"
#include "GameState.hpp"

#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
/**
 * \class Worm
 * \brief Klasa reprezentujaca robala
 *
 * Klasa dziedziczy po sf::Drawable, co oznacza, ze oiekty tej klasy mozna rysowac bezposrednio w sf::RenderWindow.
 * Posiada interfejs, dzieki ktoremu klasy WormLayer oraz TowerLayer moga decydowac, co ma sie dziac z robalami.
 * Kazdy robal to autonomiczny obiekt, ktory porusza sie po sciezce przeslanej z WormLayer do funkcji go().
 * W konstruktorze okresla sie jakiego rodzaju ma byc robal, co wplywa na jego statystyki: punkty zycia, predkosc, wartosc, czy lata itp.
 *
 */
class Worm : public sf::Drawable {
public:
	/**
	 * Konstruktor okreslajacy rodzaj robaka. Ustawia go tez na wejsciu planszy.
	 * \param type Typ robaka
	 */
	Worm(int type);


	/**
	 * Funkcja zadajaca obrazenia robakowi.
	 * \param attack Obrazenia ktore ma odniesc cel
	 * \return true Jesli robak przezyl
	 * \return false Jesli robak zginal
	 */
	bool dmg(int attack);

	/**
	 * Funkcja przesuwajaca robaka po sciezce.
	 * \param time Czas, ktory minal od ostatniego przesuniecia
	 * \param path Sciezka wyznaczona przez obiekt klasy WormLayer
	 * \return true Jesli robak dotarl do wyjscia
	 * \return false Jesli robak nie dotarl do wyjscia
	 */
	bool go(float time,std::vector<std::vector<int> > path);
	/**
	 * Funkcja okreslajaca odleglosc robaka od srodka kwadratu z Board::board o zadanych wspolrzednych.
	 * Bardzo pomocna przy wybieraniu celu dla wiezyczki
	 * \param x Wspolrzedna x wiezy
	 * \param y Wspolrzedna y wiezy
	 * \return float Odleglosc od zadanej wiezy
	 */
	float distance(int x, int y);

	/**
	 * Przeladowana funkcja z klasy sf::Drawable
	 */
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	/**
	 * Destruktor
	 */
	virtual ~Worm(){}

// zestaw setterow i getterow
	int getValue(){
		return _value;
	}

	bool isFlying(){
		return _flying;
	}

	sf::Vector2<float> getPos(){
		return _pos;
	}

	static bool isDead(const Worm & worm){
		return !worm._alive;
	}

	void setSprite(sf::Sprite s) {
		_sprite = s;
	}

	int getType() const {
		return _type;
	}

	int getDist(){
		return _dist;
	}

	friend class WormLayer;
private:
	sf::Sprite getSprite(int type); //wycina z tekstury odpowiedni dla typu robaka fragment
	sf::Vector2<float> _dir;
	sf::Vector2<float> _pos;
	int _lastX;
	int _lastY;
	int _health=0;
	bool _alive=true; //mozliwe ze zbedne
	sf::Clock _time; // czas potrzebny do animacji robakow (klatek)
	int _rotate; // trzyma obrot sprite'a [0,1,2,3]
	int _dist; // current distance form exit

// consty
	sf::Sprite _sprite;
	int _value;
	float _v;
	int _type;
	bool _flying;
	int _max_health;
	int _lifes;

	float len(sf::Vector2<float> a){
				return sqrt(a.x*a.x+a.y*a.y);
			}

};


#endif /* WORM_HPP_ */
