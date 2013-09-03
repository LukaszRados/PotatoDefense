#ifndef TOWER_HPP_
#define TOWER_HPP_

#include "Clickable.hpp"
#include "ToString.hpp"
#include "Worm.hpp"
#include "PausableClock.hpp"

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
	int getRange() const;
	int getRange(int) const;
	void levelUp();
	sf::Vector2f getPosition();
	virtual std::string getDesc(int) const;
	static int  _stats[3][3][5];
	static std::string _desc[3][3];

	friend class TowerLayer;
protected:
	int _level = 1;
	int _no;
	int _range;
	int _damage;
	int _reloadTime;
	PausableClock _time;
	bool _firstShot;
	Worm * _target;
	int _antiAir;
	void setStats(int,int);
	sf::Sound _sound;
};


#endif /* TOWER_HPP_ */
