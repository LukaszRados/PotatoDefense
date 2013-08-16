#ifndef WALL_HPP_
#define WALL_HPP_

#include "Clickable.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Wall : public Clickable {
public:
	Wall();
	virtual ~Wall();
	virtual void firstClick();
	virtual Clickable* secondClick(int, int);
	virtual std::string getName() const;
};


#endif /* WALL_HPP_ */
