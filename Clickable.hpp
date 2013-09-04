#ifndef CLICKABLE_HPP_
#define CLICKABLE_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Clickable {
public:
	Clickable();
	virtual ~Clickable();
	virtual void setX(int);
	virtual void setY(int);
	virtual int getX() const;
	virtual int getY() const;
	virtual sf::IntRect getSprite() const;
	virtual std::string getName() const = 0;
	virtual std::string getDesc() const;
	virtual void save(std::ostream &) const;
	virtual bool load(std::istream &);
protected:
	unsigned int _x = 0;
	unsigned int _y = 0;
	sf::IntRect _sprite;
	std::string _desc = "";

};


#endif /* CLICKABLE_HPP_ */
