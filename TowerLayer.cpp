#include "TowerLayer.hpp"

TowerLayer::TowerLayer(sf::RenderWindow *w):Layer(w) {
	int tx, ty;

	for(int i = 0; i < 3; ++i) {
		TowerBuilder *tmp = new TowerBuilder(i);
		tx = Board::width - (i + 2);
		ty = Board::height - 2;
		tmp->setX(tx);
		tmp->setY(ty);

		Board::board[ty][tx] = tmp;
		_builders.push_back(tmp);
	}

	_next = new BgLayer(w);

}

void TowerLayer::parseEvent(sf::Event &event) {
	if(_next != 0) {
		_next->parseEvent(event);
	}

	switch(event.type) {

	case sf::Event::MouseButtonPressed:
		int x = event.mouseButton.x / 40;
		int y = event.mouseButton.y / 40;

		//if(x < 1 || x > Board::width - 2 || y < 1 || y > Board::height - 2) return;

		// jezeli kliknieto w buildera - ustaw go w buforze
		// jesli nie:
			// bufor pusty: nic nie rob
			// bufor cos ma: postaw wiezyczke

		bool builder = false;

		for(auto i : _builders) {
			if(i->getX() == x && i->getY() == y) {
				TowerBuilder *tmp = (TowerBuilder*)i;
				builder = true;

				Board::buffer = tmp;

				break;
			}
		}

		for(auto i : _toDraw) {
			if(i != 0 && i->getX() == x && i->getY() == y && Board::buffer == 0) {
				std::cout << "I dare you, I double dare you!" << std::endl;
				builder = true;

				Board::buffer = i;
				// dodaj okienko dialogowe
				_dialog = new Dialog(((Tower*)i)->getLevel() < 3, x, y);

				break;
			}
		}

		if(!builder && Board::buffer != 0 && Board::buffer->getName() == "towerBuilder") {
			if(Board::board[y][x] == 0) {
				TowerBuilder *b = (TowerBuilder*)Board::buffer;

				if(GameState::money > b->getCost(0)) {

					Tower* t = (Tower*)b->secondClick(x, y);

					Board::board[y][x] = t;
					_toDraw.push_back(t);

					GameState::money -= b->getCost(0);
					std::cout << "Yep, you got: $" << GameState::money << std::endl;

				}
				else {
					std::cout << "Not enough money, sorry" << std::endl;
				}

				Board::buffer = 0;
			}
		}
		else if(!builder && Board::buffer != 0 && Board::buffer->getName() == "tower") {
			Tower* tmp = (Tower*)Board::buffer;
			int level = tmp->getLevel();
			int number = tmp->getNumber();

			if(y == tmp->getY() + 1) {
				if(x < tmp->getX()) {
					if(level >= 3) {
						std::cout << "No more leveling, man!" << std::endl;
						Board::buffer = 0;
					}
					else {
						std::cout << "Level it up for god's sake!" << std::endl;
						int nextLevelCost = TowerBuilder(number).getCost(level);

						if(GameState::money >= nextLevelCost) {
							GameState::money -= nextLevelCost;
							tmp->levelUp();
						}
						else {
							std::cout << "Sorry, bro, no money." << std::endl;
						}
						Board::buffer = 0;

					}
				}
				else if(x == tmp->getX()) {
					std::cout << "Sell it, sell this shit!" << std::endl;
					int levelCost = TowerBuilder(number).getSellingCost(level);
					std::cout << levelCost << std::endl;
					GameState::money += levelCost;

					delete Board::board[y][x];

					for(int i = 0; i < _toDraw.size(); ++i) {
						if(_toDraw[i]->getX() == x && _toDraw[i]->getY() == y - 1) {

							//_toDraw[i] = 0;
							break;
						}
					}

					int off = 0;
					while(off < _toDraw.size()) {
						if(_toDraw[off] != 0 && _toDraw[off]->getX() == x && _toDraw[off]->getY() == y - 1) {
							break;
						}
						++off;
					}

					std::cout << off << std::endl;

					_toDraw.erase(_toDraw.begin() + off);

					//_toDraw[i] = 0;

					std::cout << "Yep, you got: $" << GameState::money << std::endl;
					Board::buffer = 0;

				}
				else {
					Board::buffer = 0;
				}

				if(_dialog != 0) {
					delete _dialog;
					_dialog = 0;
				}

			}
		}

		break;

	}
}

void TowerLayer::draw() {
	if(_next != 0) {
		_next->draw();
	}

	int tx, ty;

	sf::Texture sprites;
	if(!sprites.loadFromFile("graphics/towers.png")) {
		std::cout << "Error: Cannot load towers.png!";
		return;
	}

	for(auto i : _builders) {
		tx = i->getX();
		ty = i->getY();

		sf::Sprite sprite;
		sprite.setTexture(sprites);
		sprite.setTextureRect(i->getSprite());
		sprite.setPosition(tx * Board::fieldW, ty * Board::fieldH);

		_window->draw(sprite);
	}

	for(auto i : _toDraw) {
		if(i != 0) {
			tx = i->getX();
			ty = i->getY();

			sf::Sprite sprite;
			sprite.setTexture(sprites);
			sprite.setTextureRect(i->getSprite());
			sprite.setPosition(tx * Board::fieldW, ty * Board::fieldH);

			_window->draw(sprite);
		}
	}

	// dialog, draw dialog!
	if(_dialog != 0) {
		int x = _dialog->getX();
		int y = _dialog->getY();
		bool opt = _dialog->getOptions();

		sf::Texture s;
		if(!s.loadFromFile("graphics/dialog.png")) {
			std::cout << "Error: Cannot load dialog.png!";
			return;
		}

		sf::Sprite sprite;
		sprite.setTexture(s);
		if(_dialog->getOptions()) {
			sprite.setTextureRect(sf::IntRect(0, 0, 120, 40));
		}
		else {
			sprite.setTextureRect(sf::IntRect(0, 40, 120, 40));
		}
		sprite.setPosition((x - 1) * Board::fieldW, (y + 1) * Board::fieldH);

		_window->draw(sprite);
	}
}
