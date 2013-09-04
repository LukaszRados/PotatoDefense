#ifndef DIALOG_CPP_
#define DIALOG_CPP_

#include "Clickable.hpp"

class Dialog {
public:
	Dialog(bool, int, int);
	int getX() const;
	int getY() const;
	bool getOptions() const;
	void setOptions(bool);
private:
	bool _options;
	int _x;
	int _y;
};

#endif /* DIALOG_CPP_ */
