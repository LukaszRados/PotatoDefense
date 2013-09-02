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

	_next = new WormLayer(w);

	_active = sf::RectangleShape(sf::Vector2f(40, 40));
	_active.setOutlineColor(sf::Color(255, 255, 255, 100));
	_active.setOutlineThickness(1);
	_active.setFillColor(sf::Color::Transparent);
	_active.setPosition(-100, -100);

	_shadow = sf::Sprite();
	_shadow.setTexture(*(GameState::textures["towers"]));
	_shadow.setTextureRect(sf::IntRect(0, 120, 40, 40));
	_shadow.setPosition(-100, -100);

	_ranges = {
		sf::CircleShape(),
		sf::CircleShape()
	};

	for(auto i = _ranges.begin(); i < _ranges.end(); ++i) {
		i->setPosition(-100,-100);
		i->setRadius(0);
		i->setFillColor(sf::Color(0, 155, 255, 100));
		i->setOutlineColor(sf::Color(0, 155, 255, 180));
		i->setOutlineThickness(2);
	}
}

TowerLayer::~TowerLayer() {
	if(_next != 0) {
		delete _next;
	}

	for(int i = 0; i < Board::height; ++i) {
		for(int j = 0; j < Board::width; ++j) {
			if(Board::board[i][j] != 0) {
				Board::board[i][j] = 0;
			}
		}
	}

	for(auto i = _builders.begin(); i < _builders.end(); ++i) {
		delete *i;
	}

	for(auto i = _towers.begin(); i != _towers.end(); ++i) {
		if(*i != 0) {
			delete *i;
		}
	}

	Board::buffer = 0;
}

void TowerLayer::parseEvent(sf::Event &event) {
	if(_next != 0) {
		_next->parseEvent(event);
	}

	int x, y;

	switch(event.type) {
	case sf::Event::MouseButtonPressed:
		if(event.mouseButton.button == sf::Mouse::Button::Right) {
			Board::buffer = 0;

			if(_dialog != 0) {
				delete _dialog;
				_dialog = 0;
			}

			break;
		}

		x = event.mouseButton.x / 40;
		y = event.mouseButton.y / 40;

		_ranges[0].setPosition(-100,-100);
		_ranges[0].setRadius(0);

		if(Board::buffer == 0 && _dialog == 0) {
			for(auto i : _builders) {
				if(i->getX() == x && i->getY() == y) {
					TowerBuilder *tmp = (TowerBuilder*)i;

					Board::buffer = tmp;
					GameState::info = "Click to build new tower.";

					return;
				}
			}

			for(auto i : _toDraw) {
				if(i != 0 && i->getX() == x && i->getY() == y) {
					Board::buffer = i;
					Tower* tmp = (Tower*)i;

					_dialog = new Dialog(tmp->getLevel() < 3, x, y);

					int r = tmp->getRange(tmp->getLevel());
					_ranges[0].setRadius(r);
					_ranges[0].setPosition(x * 40 - r + 20, y * 40 - r + 20);

					return;
				}
			}
		}

		if(Board::buffer != 0 && Board::buffer->getName() == "towerBuilder") {
			auto tmp=Board::getBoardAsInts();
			tmp[y][x]=1;

			if(Board::board[y][x] == 0 && ((WormLayer*)_next)->pathExists(tmp) && WormLayer::isFree(x,y)) {
				TowerBuilder *b = (TowerBuilder*)Board::buffer;

				if(GameState::money > b->getCost(0)) {

					Tower* t = (Tower*)b->secondClick(x, y);

					Board::board[y][x] = t;
					_towers.push_back(t);

					_toDraw.push_back(t);

					GameState::money -= b->getCost(0);
					GameState::info = "New tower built ($ " + toString(b->getCost(0)) + ").";
					((WormLayer*)_next)->setPath(Board::getBoardAsInts());
				}
				else {
					GameState::info = "Not enough money ($ " + toString(b->getCost(0)) + " required).";
				}

				Board::buffer = 0;
			}
			else {
				Board::buffer = 0;
			}
		}
		else if(Board::buffer != 0 && Board::buffer->getName() == "tower") {
			Tower* tmp = (Tower*)Board::buffer;
			int level = tmp->getLevel();
			int number = tmp->getNumber();

			if(y == tmp->getY() + 1) {
				if(x < tmp->getX()) {
					if(level >= 3) {
						GameState::info = "Max. level reached.";
						Board::buffer = 0;
					}
					else {
						int nextLevelCost = TowerBuilder(number).getCost(level);

						if(GameState::money >= nextLevelCost) {
							GameState::money -= nextLevelCost;
							tmp->levelUp();
							GameState::info = "New level set: " + toString(level + 1);
						}
						else {
							GameState::info = "Not enough money \n($ " + toString(nextLevelCost) + " required).";
						}
						Board::buffer = 0;

					}
				}
				else if(x == tmp->getX()) {
					int levelCost = TowerBuilder(number).getSellingCost(level);
					GameState::money += levelCost;


					//delete Board::board[y - 1][x];	// uzycie tego delete powoduje segmentation fault
					_towers.remove((Tower*)Board::board[y-1][x]);

					Board::board[y - 1][x] = 0;

					// zeby przeliczylo po sprzedaniu
					((WormLayer*)_next)->setPath(Board::getBoardAsInts());
					unsigned int off = 0;
					while(off < _toDraw.size()) {
						if(_toDraw[off] != 0 && _toDraw[off]->getX() == x && _toDraw[off]->getY() == y - 1) {
							break;
						}
						++off;
					}

					_toDraw.erase(_toDraw.begin() + off);

					GameState::info = "Tower sold ($ " + toString(levelCost) + ").";
					Board::buffer = 0;
				}
				else {
					Board::buffer = 0;
				}
//
			}

			if(_dialog != 0) {
				Board::buffer = 0;
				delete _dialog;
				_dialog = 0;
			}
		}

		break;
//*********************** End of case ButtonPressed ***************************************************//

	case sf::Event::MouseMoved:
		x = event.mouseMove.x / 40;
		y = event.mouseMove.y / 40;

		_active.setPosition(-100, -100);
		_shadow.setPosition(-100, -100);

		_ranges[1].setPosition(-100, -100);
		_ranges[1].setRadius(0);

		if(Board::buffer == 0 || Board::buffer->getName() != "tower") {
			_ranges[0].setPosition(-100, -100);
			_ranges[0].setRadius(0);
		}

		GameState::info = "";

		for(auto i : _builders) {
			if(i->getX() == x && i->getY() == y) {
				GameState::info = ((TowerBuilder*)i)->getDesc();
				return;
			}
		}

		for(auto i : _towers) {
			if(i->getX() == x && i->getY() == y) {
				Tower *active = (Tower*)i;
				GameState::info = active->getDesc(active->getLevel() - 1);
				break;
			}
		}

		if(x > 14) {
			GameState::info = "";
			return;
		}

		auto tmp=Board::getBoardAsInts();
		tmp[y][x]=1;
		bool pathExists = ((WormLayer*)_next)->pathExists(tmp);

		if(_dialog != 0) {
			Tower* tmp = (Tower*)Board::buffer;
			TowerBuilder tb(tmp->getNumber());
			if(tmp->getY() + 1 == y) {
				switch(x - tmp->getX()) {
				case 0:
					GameState::info = "Sale price is $ " + toString(tb.getSellingCost(tmp->getLevel()));
					break;

				case 1:
					GameState::info = "Cancel";
					break;

				case -1:
					if(tmp->getLevel() == 3) {
						GameState::info = "Tower reached max. level";
					}
					else {
						int lvl = tmp->getLevel();
						int r = tmp->getRange(lvl + 1);
						GameState::info = "Upgrading to level " + toString(lvl + 1) + "\ncosts $ " + toString(tb.getCost(lvl)) + "\n" + tmp->getDesc(lvl);
						_ranges[1].setRadius(r);
						_ranges[1].setPosition(tmp->getX() * 40 - r + 20, tmp->getY() * 40 - r + 20);
					}
					break;

				default:
					GameState::info = "";
					break;
				}
			}
			else {
				GameState::info = "";
			}
			return;
		}

		_active.setPosition(x * 40, y * 40);
		_shadow.setPosition(x * 40, y * 40);

		if(Board::board[y][x]) {
			_active.setOutlineColor(sf::Color(255, 0, 0, 125));
			_shadow.setPosition(-100, -100);
			_ranges[0].setPosition(-100, -100);
			_ranges[0].setRadius(0);
		}
		else {
			_active.setOutlineColor(sf::Color(255, 255, 255, 100));
		}

		if(Board::buffer == 0 || Board::buffer->getName() != "towerBuilder") {
			_shadow.setPosition(-100, -100);
			_ranges[0].setPosition(-100, -100);
			_ranges[0].setRadius(0);
		}
		else if(Board::buffer != 0 && Board::buffer->getName() == "towerBuilder" && pathExists && WormLayer::isFree(x,y)) {
			_shadow.setTextureRect(sf::IntRect(Board::buffer->getSprite().left, 120, 40, 40));

			if(!Board::board[y][x]) {
				TowerBuilder *tb = (TowerBuilder*)Board::buffer;
				int range = Tower::_stats[tb->getTowerNumber()][0][0];

				_ranges[0].setRadius(range);
				_ranges[0].setPosition(x * 40 - range + 20, y * 40 - range + 20);
			}
		}
		else if(!pathExists || !WormLayer::isFree(x,y)) {
			GameState::info = "This place is not avaible.";
			_shadow.setPosition(-100, -100);
			_ranges[0].setPosition(-100, -100);
			_ranges[0].setRadius(0);
		}

		if(!pathExists || !WormLayer::isFree(x,y)) {
			_active.setOutlineColor(sf::Color(255, 0, 0, 125));
			_ranges[0].setPosition(-100, -100);
			_ranges[0].setRadius(0);
		}
		break;

	}
}

void TowerLayer::update(){
	if( _next != 0)
		_next->update();

	for(auto i : _towers){
		i->shoot(WormLayer::worms);
	}
}

void TowerLayer::draw() {
	int tx, ty;

	_window->draw(_ranges[1]);		// ew. nowy zasieg wiezyczki
	_window->draw(_ranges[0]);		// rysujemy jako pierwsze, zeby nic nie przykrywalo

	for(auto i : _builders) {
		tx = i->getX();
		ty = i->getY();

		sf::Sprite sprite;
		sprite.setTexture(*(GameState::textures["towers"]));
		sprite.setTextureRect(i->getSprite());
		sprite.setPosition(tx * Board::fieldW, ty * Board::fieldH);

		_window->draw(sprite);
	}

	for(auto i : _toDraw) {
		if(i != 0) {
			tx = i->getX();
			ty = i->getY();

			sf::Sprite sprite;
			sprite.setTexture(*(GameState::textures["towers"]));
			sprite.setTextureRect(i->getSprite());
			sprite.setPosition(tx * Board::fieldW, ty * Board::fieldH);

			_window->draw(sprite);
		}
	}

	// dialog, draw dialog!

	_window->draw(_active);
	_window->draw(_shadow);

	if(_next != 0) {
		_next->draw();
	}

	if(_dialog != 0) {
		int x = _dialog->getX();
		int y = _dialog->getY();

		sf::Sprite sprite;
		sprite.setTexture(*(GameState::textures["dialog"]));
		if(_dialog->getOptions()) {
			sprite.setTextureRect(sf::IntRect(0, 0, 120, 40));
		}
		else {
			sprite.setTextureRect(sf::IntRect(0, 40, 120, 40));
		}
		sprite.setPosition((x - 1) * Board::fieldW, (y + 1) * Board::fieldH);

		_window->draw(sprite);
	}

	// here be dragons. and shots drawing

}
