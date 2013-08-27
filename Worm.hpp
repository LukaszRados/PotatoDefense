#ifndef WORM_HPP_
#define WORM_HPP_

#include "Board.hpp"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>



class Worm : public sf::Drawable {
public:
	Worm(int); //konstruktor okreslajacy rodzaj robaka


	/** Funkcja ktora zadaje obrazenia
	 *  @return true-jesli robak przezyl | false - jesli umarl
	 */
	bool dmg(int);

	/** Funkcja iscia
	 *  pos+=dir*v*time
	 *  time - czas od ostatniego przesunieca
	 *  dziekie temu bedzie latwo dostosowac predkosc
	 *  @return false - jesli ciagle idzie | true - jesli przeszla plansze
	 */
	bool go(int);


	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	virtual ~Worm(){}

	// wczytanie textury, zeby bylo raz
	static void loadTexture();
//getery (pisze tu bo by bylo duzo roboty :)
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
	// frienship for accessing private members
	friend class WormLayer;
private:
	static sf::Texture _texture; //tekstura gdzie będą wszystkie sprite'y, zeby tylko raz ladowac z dysku
	sf::Sprite getSprite(int type); //wycina z tekstury odpowiedni dla typu robaka fragment

	sf::Vector2<float> _dir;
	sf::Vector2<float> _pos;
	int _health=0;
	bool _alive=true; //mozliwe ze zbedne


// consty
	sf::Sprite _sprite;
	int _value;
	float _v;
	int _type;
	bool _flying;
	int _max_health;
};


#endif /* WORM_HPP_ */
