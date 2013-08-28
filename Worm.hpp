#ifndef WORM_HPP_
#define WORM_HPP_

#include "Board.hpp"
#include "GameState.hpp"
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
	bool go(int,std::vector<std::vector<int> >);


	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	virtual ~Worm(){}

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

	void setSprite(sf::Sprite s) {
		_sprite = s;
	}

	int getType() const {
		return _type;
	}
	// frienship for accessing private members
	friend class WormLayer;
private:
	static int _iter; // sluzy do animacji robakow (tzn. przelaczania klatek)
	sf::Sprite getSprite(int type); //wycina z tekstury odpowiedni dla typu robaka fragment
	sf::Vector2<float> _dir;
	sf::Vector2<float> _pos;
	int _lastX;
	int _lastY;
	int _health=0;
	bool _alive=true; //mozliwe ze zbedne


// consty
	sf::Sprite _sprite;
	int _value;
	float _v;
	int _type;
	bool _flying;
	int _max_health;


	static float len(sf::Vector2<float> a){
			return sqrt(a.x*a.x+a.y*a.y);
		}
};


#endif /* WORM_HPP_ */
