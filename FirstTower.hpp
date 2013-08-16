#ifndef FIRSTTOWER_HPP_
#define FIRSTTOWER_HPP_

#include "Tower.hpp"

class FirstTower : public Tower {
public:
	FirstTower();
	virtual ~FirstTower();
	virtual void firstClick();
	virtual Clickable* secondClick(int x, int y);
private:

};

#endif /* FIRSTTOWER_HPP_ */
