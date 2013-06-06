#ifndef WORM_HPP_
#define WORM_HPP_

#include "Object.hpp"

class Worm : public Object {
public:

private:
	int _hp = 100;
	int _speed;
	bool _fly = false;
	/**
	 * _rotation: [0 - north
	 * 			   1 - east
	 * 			   2 - south
	 * 			   3 - west ]
	 */
	int _rotation = 0;
};

#endif /* WORM_HPP_ */
