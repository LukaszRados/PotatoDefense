#include "Dialog.hpp"

Dialog::Dialog(bool opt, int x, int y):_options(opt){
	setX(x);
	setY(y);
}

bool Dialog::getOptions() const {
	return _options;
}

void Dialog::setOptions(bool opt) {
	_options = opt;
}

std::string Dialog::getName() const {
	return "dialog";
}
