#include "Dialog.hpp"

Dialog::Dialog(bool opt, int x, int y):_options(opt), _x(x), _y(y) {
}

int Dialog::getX() const {
	return _x;
}

int Dialog::getY() const {
	return _y;
}

bool Dialog::getOptions() const {
	return _options;
}
