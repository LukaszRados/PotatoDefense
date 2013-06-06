#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <vector>

class Object : public sf::Drawable {
public:
	virtual ~Object() = 0;
	virtual void step() = 0;

	static void setWorms(std::vector<Object> &worms) {

	}

	static std::vector<Object> *_worms;
	static std::vector<Object> *_towers;
	static std::vector<std::vector<int>> *_map;
	static std::vector<std::vector<int>> *_path;

protected:
	int _x = -1;
	int _y = -1;
};

#endif /* OBJECT_HPP_ */
