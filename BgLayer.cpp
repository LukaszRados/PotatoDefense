#include "BgLayer.hpp"

BgLayer::BgLayer(sf::RenderWindow *w):Layer(w) {
	GameState::globalTime.restart();

	_next=new TowerLayer(w);
}

BgLayer::~BgLayer() {
	if(_next != 0) {
		delete _next;
	}
}

void BgLayer::parseEvent(sf::Event &event) {
	if(_next != 0) {
		_next->parseEvent(event);
	}
}

void BgLayer::update(){
	if( _next != 0 )
		_next->update();
}
void BgLayer::draw() {
	sf::Sprite sprite;
	sprite.setTexture(*(GameState::textures["bg"]));
	sprite.setTextureRect(sf::IntRect(0, 0, 600, 600));
	sprite.setPosition(0, 0);

	_window->draw(sprite);

	sprite.setTexture(*(GameState::textures["panel"]));
	sprite.setTextureRect(sf::IntRect(0, 0, 200, 600));
	sprite.setPosition(600, 0);
	_window->draw(sprite);

	sprite.setTexture(*(GameState::textures["volume"]));
	sprite.setTextureRect(sf::IntRect(0, (GameState::music ? 0 : 1) * 40, 40, 40));
	sprite.setPosition(720, 0);
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

	text.setString(GameState::info);
	text.setPosition(610, 170);

	_window->draw(text);

	int seconds = (int)GameState::globalTime.getElapsedTime().asSeconds();
	std::string time=toString(seconds/60)+":"+(seconds % 60 < 10 ? "0" : "")+toString(seconds % 60);

	text.setString(time);
	text.setPosition(650,10);
	_window->draw(text);

	if(_next != 0) {
		_next->draw();
	}
}
