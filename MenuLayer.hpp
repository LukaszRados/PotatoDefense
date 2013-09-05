#ifndef MENULAYER_HPP_
#define MENULAYER_HPP_

#include "Layer.hpp"
#include "BaseLayer.hpp"
#include "ToString.hpp"
#include "GameState.hpp"


#include <iostream>


/**
 * \class MenuLayer
 * \brief Warstwa odpowiedzialna za menu glowne gry.
 *
 * Klasa wyswietla menu glowne jesli trzeba, a takze jest odpowiedzialna za pelnoekranowe komunikaty podczas gry:
 * <ul>
 * <li>GameOver</li>
 * <li>Victory</li>
 * <li>Next wave in...</li>
 * <li>How to play </li>
 * </ul></br>
 *
 */
class MenuLayer : public Layer {
public:
	/**
	 * Konstruktor
	 */
	MenuLayer(sf::RenderWindow*);
	virtual ~MenuLayer();
	/**
	 * Procedura do obslugi zdarzen.
	 */
	virtual void parseEvent(sf::Event &event);
	/**
	 * Procedura do rysowania warstwy.
	 */
	virtual void draw();
	/**
	 * Procedura aktualizujaca logike warstwy - przemieszczanie sie robali, strzelanie wiez...
	 */
	virtual void update();
private:
	struct MenuPosition {
		int no;			// ID
		int state;		// enabled / disabled
		bool active;	// hover
		States onClick;	// state changed on click
	};

	struct Tip {
		int x;
		int y;
		std::string text;
	};

	MenuPosition _menu[4] = {
		{0, 0, false, States::Load},
		{1, 1, false, States::Game},
		{2, 1, false, States::HowToPlay},
		{3, 1, false, States::Exit}
	};

	std::vector<Tip> _tips = {
		{660, 500, "Click here to build new tower"},
		{300, 340, "Use towers to create labyrinth"},
		{220, 220, "Click on existing tower to see options"},
		{180, 260, "Upgrade towers to increase damage and range"},
		{490, 260, "Don't let bugs eat your vegetables!"},
		{-20, 260, "Some bugs can fly! \nYou need special towers to destroy them!"},
		{730, 20, "Remember - you are a poor farmer..."},
		{580, 60, "... and you are mortal!"},
		{-100, -100, "Have fun!"}
	};

	int tip = 0;

	sf::Sprite _sprite = sf::Sprite();
};

#endif /* MENULAYER_HPP_ */
