#ifndef TOWER_HPP_
#define TOWER_HPP_

#include "Object.hpp"

class Tower : public Object {
public:
	void searchClosestTarget();
	void upgrade();
	static const int cost[];
private:
	int _dmg;
	int _range;
	int _fireRate;
	int _level;
};


#endif /* TOWER_HPP_ */
