#include "BgLayer.hpp"

BgLayer::BgLayer(sf::RenderWindow *w):Layer(w) {
	GameState::textures["bg"] = new sf::Texture();
	GameState::textures["bg"]->loadFromFile("graphics/bg.png");
}

void BgLayer::parseEvent(sf::Event &event) {
	if(_next != 0) {
		_next->parseEvent(event);
	}
}

void BgLayer::draw() {
	if(_next != 0) {
		_next->draw();
	}

//	sf::Texture sprites = ;

	sf::Sprite sprite;
	sprite.setTexture(*(GameState::textures["bg"]));
	sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	sprite.setPosition(0, 0);

	_window->draw(sprite);

	sf::Font font;
	font.loadFromFile("graphics/ptsans.ttf");

	sf::Text text("$ " + toString(GameState::money), font);
	text.setCharacterSize(15);
	text.setColor(sf::Color::White);
	text.setPosition(800 - (text.getLocalBounds().width + 10), 50);

	_window->draw(text);

	text.setString(toString(GameState::lifes));
	text.setPosition(700 - (text.getLocalBounds().width + 10), 90);

	_window->draw(text);

	text.setString(toString(GameState::wave));
	text.setPosition(800 - (text.getLocalBounds().width + 10), 90);

	_window->draw(text);


}
