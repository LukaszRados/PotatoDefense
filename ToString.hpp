#ifndef TOSTRING_HPP_
#define TOSTRING_HPP_

#include <string>
#include <sstream>

/**
 * Szablon funkcji do zamiany dowolnego typu, ktory posiada operator << dla strumienia std::ostream.
 * \param Obiekt do zamiany na napis
 * \return Obiekt std::string z reprezentacja napisowa argumentu
 */
template<typename T>
std::string toString(T val) {
	std::stringstream str;
	str << val;
	return str.str();
}

/**
 * Szablon funkcji do zamiany napisu na typ okreslony w parametrze szablonu. Wymagany przeladowany operator >> dla strumienia std::istream.
 * \param Napis do zamiany na obiekt
 * \return Obiekt klasy okreslonej w parametrze szablonu
 */
template<typename T>
T stringTo(std::string txt) {
	std::stringstream str(txt);
	T val;
	str >> val;
	return val;
}

#endif /* TOSTRING_HPP_ */
