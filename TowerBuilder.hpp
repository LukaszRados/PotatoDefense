#ifndef TOWERBUILDER_HPP_
#define TOWERBUILDER_HPP_

#include "Clickable.hpp"
#include "Tower.hpp"
#include <SFML/Graphics.hpp>

class TowerBuilder : public Clickable {
public:
	TowerBuilder();
	TowerBuilder(int);
	virtual ~TowerBuilder();
	virtual void firstClick();
	Clickable* secondClick(int, int);
	int getCost(int lvl) const;
	int getSellingCost(int lvl) const;
	Tower* putTower();
	virtual std::string getName() const;
	virtual std::string getDesc() const;


protected:
	int _towerNumber = 0;
};


#endif /* TOWERBUILDER_HPP_ */
