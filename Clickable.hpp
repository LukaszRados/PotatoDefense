#ifndef CLICKABLE_HPP_
#define CLICKABLE_HPP_

#include <SFML/Graphics.hpp>
#include <string>

class Clickable {
public:
	Clickable();
	virtual ~Clickable();
	virtual void setX(unsigned int);
	virtual void setY(unsigned int);
	virtual unsigned int getX() const;
	virtual unsigned int getY() const;
	virtual sf::IntRect getSprite() const;
	virtual std::string getName() const = 0;
	virtual std::string getDesc() const;

protected:
	unsigned int _x = 0;
	unsigned int _y = 0;
	sf::IntRect _sprite;
	std::string _desc = "";

};


#endif /* CLICKABLE_HPP_ */
