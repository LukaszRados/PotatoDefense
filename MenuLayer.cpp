#include "MenuLayer.hpp"

MenuLayer::MenuLayer(sf::RenderWindow *w):Layer(w) {
	GameState::textures["splash"] = new sf::Texture();
	GameState::textures["splash"]->loadFromFile("graphics/splash.png");

	GameState::textures["menu"] = new sf::Texture();
	GameState::textures["menu"]->loadFromFile("graphics/menu.png");

	GameState::textures["pause"] = new sf::Texture();
	GameState::textures["pause"]->loadFromFile("graphics/pause.png");

	GameState::textures["gameover"] = new sf::Texture();
	GameState::textures["gameover"]->loadFromFile("graphics/gameover.png");

	GameState::sounds["menu"] = new sf::Music();
	GameState::sounds["menu"]->openFromFile("music/menu.ogg");

	GameState::state = States::MainMenu;
	GameState::reset();
}

MenuLayer::~MenuLayer() {

}

void MenuLayer::parseEvent(sf::Event &event) {
	switch(event.type) {
	case sf::Event::Closed:
		_window->close();
		break;

	case sf::Event::KeyPressed:
		if(event.key.code == sf::Keyboard::Escape) {
			_window->close();
		}
		else if(event.key.code == sf::Keyboard::P) {
			if(GameState::state == States::Game) {
				GameState::state = States::Paused;
			}
			else if(GameState::state == States::Paused) {
				GameState::state = States::Game;
			}
		}
		break;

	case sf::Event::MouseButtonPressed:
		if(GameState::state == States::MainMenu) {
			int x = event.mouseButton.x;
			int y = event.mouseButton.y;

			for(auto i : _menu) {
				sf::Rect<int> rect = sf::Rect<int>(300, 280 + i.no * 60, 200, 50);
				if(rect.contains(x, y) && i.state == 1) {
					GameState::state = i.onClick;
				}
			}

			if(GameState::state == States::Game) {
				_next = new BaseLayer(_window);
			}
		}
		else if(GameState::state == States::HowToPlay) {
			GameState::state = States::MainMenu;
		}
		else if(GameState::state == States::Paused) {
			GameState::state = States::Game;
		}
		else if(GameState::state == States::GameOver) {
			GameState::state = States::MainMenu;
			delete _next;
			_next = 0;
			GameState::reset();
		}
		break;

	case sf::Event::MouseMoved:
		if(GameState::state == States::MainMenu) {
			int x = event.mouseMove.x;
			int y = event.mouseMove.y;
			int active = -1;
			bool hover = false;

			for(int i = 0; i < 4; ++i) {
				sf::Rect<int> rect = sf::Rect<int>(300, 280 + _menu[i].no * 60, 200, 50);
				if(rect.contains(x, y)) {
					hover = true;

					if(_menu[i].state == 1 && !_menu[i].active) {
						_menu[i].active = true;
						active = i;
						GameState::sounds["menu"]->setVolume(50);
						GameState::sounds["menu"]->setLoop(false);
						GameState::sounds["menu"]->play();
					}
				}
			}

			if(active >= 0 || !hover) {
				for(int i = 0; i < 4; ++i) {
					if(i == active && hover) continue;
					_menu[i].active = false;
				}
			}
		}

		break;
	}

	if(GameState::state == States::Game && _next != 0) {
		_next->parseEvent(event);
	}
	else if(GameState::state == States::Exit) {
		_window->close();
	}
}

void MenuLayer::draw() {
	switch(GameState::state) {
	case MainMenu:
		_sprite.setTexture(*(GameState::textures["splash"]));
		_sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
		_sprite.setPosition(0, 0);

		_window->draw(_sprite);

		_sprite.setTexture(*(GameState::textures["menu"]));
		for(auto i : _menu) {
			int offset = 0;

			if(i.state == 0) {
				offset = 2;
			}
			else if(i.state == 1 && i.active) {
				offset = 1;
			}
			_sprite.setTextureRect(sf::IntRect(offset * 200, i.no * 50, 200, 50));
			_sprite.setPosition(300, 280 + i.no * 60);
			_window->draw(_sprite);
		}
		break;

	case Game:
		if(_next != 0) {
			_next->draw();
		}
		break;

	case Paused:
		if(_next != 0) {
			_next->draw();

			sf::RectangleShape bg = sf::RectangleShape();
			bg.setFillColor(sf::Color(255, 255, 255, 150));
			bg.setSize(sf::Vector2f(800, 600));
			bg.setPosition(0, 0);
			_window->draw(bg);

			_sprite.setTexture(*(GameState::textures["pause"]));
			_sprite.setTextureRect(sf::IntRect(0, 0, 230, 120));
			_sprite.setPosition(285, 240);
			_window->draw(_sprite);
		}
		break;

	case GameOver:
		if(_next != 0) {
			_next->draw();

			sf::RectangleShape bg = sf::RectangleShape();
			bg.setFillColor(sf::Color(255, 255, 255, 150));
			bg.setSize(sf::Vector2f(800, 600));
			bg.setPosition(0, 0);
			_window->draw(bg);

			_sprite.setTexture(*(GameState::textures["gameover"]));
			_sprite.setTextureRect(sf::IntRect(0, 0, 350, 120));
			_sprite.setPosition(225, 240);
			_window->draw(_sprite);
		}

		break;

	case HowToPlay:
		// draw 'HowToPlay' screen
		break;

	case Exit:
		break;
	}
}

void MenuLayer::update() {
	if(GameState::lifes <= 0) {
		GameState::state = States::GameOver;
	}

	if(_next != 0) {
		_next->update();
	}
}
