#ifndef TOSTRING_HPP_
#define TOSTRING_HPP_

#include <string>
#include <sstream>

/**
 * Function changing any type to string
 * (Overriden operator << required)
 */
template<typename T>
std::string toString(T val) {
	std::stringstream str;
	str << val;
	return str.str();
}

/**
 * Function changing string to any type
 * (Overriden operator >> required)
 */
template<typename T>
T stringTo(std::string txt) {
	std::stringstream str(txt);
	T val;
	str >> val;
	return val;
}

#endif /* TOSTRING_HPP_ */
