#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>

class Object : public sf::Drawable {
public:
	virtual ~Object() = 0;
	virtual void step() = 0;

protected:
	int _x = -1;
	int _y = -1;
	std::vector<Object> *_worms;
	std::vector<Object> *_towers;
	std::vector<std::vector<int>> *_map;
	std::vector<std::vector<int>> *_path;
};

#endif /* OBJECT_HPP_ */
