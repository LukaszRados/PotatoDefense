#ifndef TOSTRING_HPP_
#define TOSTRING_HPP_

#include <string>
#include <sstream>

template<typename T>
std::string toString(T val) {
	std::stringstream str;
	str << val;
	return str.str();
}

template<typename T>
T stringTo(std::string txt) {
	std::stringstream str(txt);
	T val;
	str >> val;
	return val;
}

#endif /* TOSTRING_HPP_ */
