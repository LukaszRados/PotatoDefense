#ifndef WALL_HPP_
#define WALL_HPP_

#include "Clickable.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Wall : public Clickable {
public:
	Wall();
	Wall(int);
	virtual ~Wall();
	virtual void firstClick();
	virtual Clickable* secondClick(int, int);
	virtual std::string getName() const;
	virtual int getNumber() const;

private:
	int _number;
};


#endif /* WALL_HPP_ */
