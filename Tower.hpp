#ifndef TOWER_HPP_
#define TOWER_HPP_

#include "Clickable.hpp"
#include "ToString.hpp"
#include "Worm.hpp"

#include <SFML/Graphics.hpp>
#include <list>

class Tower : public Clickable {
public:
	Tower();
	Tower(int);
	virtual ~Tower();
	virtual void shoot(std::list<Worm> &);
	virtual std::string getName() const;
	int getLevel() const;
	int getNumber() const;
	void levelUp();
	virtual std::string getDesc(int) const;
	static int _prices[3][3];
protected:
	int _level = 1;
	int _no;
	int _range;
	int _damage;
	int _reloadTime;
	sf::Clock _time;
	bool _firstShot;
	int _antiAir;
	void setStats(int,int);

	static int  _stats[3][3][4];
};


#endif /* TOWER_HPP_ */
