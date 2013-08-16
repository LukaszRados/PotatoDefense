#ifndef CLICKABLE_HPP_
#define CLICKABLE_HPP_

#include <SFML/Graphics.hpp>

class Clickable {
public:
	Clickable();
	virtual ~Clickable();
	virtual void firstClick() = 0;
	virtual Clickable* secondClick(int, int) = 0;
	virtual void setX(unsigned int);
	virtual void setY(unsigned int);
	virtual unsigned int getX() const;
	virtual unsigned int getY() const;
	virtual sf::IntRect getSprite() const;
	virtual std::string getName() const = 0;

protected:
	unsigned int _x = 0;
	unsigned int _y = 0;
	sf::IntRect _sprite;

};


#endif /* CLICKABLE_HPP_ */
