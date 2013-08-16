#ifndef TOWER_HPP_
#define TOWER_HPP_

#include "Clickable.hpp"
#include <SFML/Graphics.hpp>
#include "ToString.hpp"

class Tower : public Clickable {
public:
	Tower();
	Tower(int);
	virtual ~Tower();
	virtual void shoot(int**);
	virtual void firstClick();
	virtual Clickable* secondClick(int, int);
	virtual std::string getName() const;
	int getLevel() const;
	int getNumber() const;
	void levelUp();
	virtual std::string getDesc() const;

protected:
	int _level = 1;
	int _no;
	int _range;
	int _damage;
	int _reloadTime;
};


#endif /* TOWER_HPP_ */
