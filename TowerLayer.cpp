//#include "TowerLayer.hpp"
//
//TowerLayer::TowerLayer(sf::RenderWindow *w):Layer(w) {
//	int tx, ty;
//
//	for(int i = 0; i < 3; ++i) {
//		TowerBuilder *tmp = new TowerBuilder(i);
//		tx = Board::width - (i + 2);
//		ty = Board::height - 2;
//		tmp->setX(tx);
//		tmp->setY(ty);
//
//		Board::board[ty][tx] = tmp;
//		_builders.push_back(tmp);
//	}
//
//	_next =new WormLayer(w);
//
//	GameState::textures["towers"] = new sf::Texture();
//	GameState::textures["towers"]->loadFromFile("graphics/towers.png");
//
//	GameState::textures["dialog"] = new sf::Texture();
//	GameState::textures["dialog"]->loadFromFile("graphics/dialog.png");
//
//}
//
//void TowerLayer::parseEvent(sf::Event &event) {
//	if(_next != 0) {
//		_next->parseEvent(event);
//	}
//
//	int x, y;
//
//	switch(event.type) {
//	case sf::Event::MouseButtonPressed:
//		x = event.mouseButton.x / 40;
//		y = event.mouseButton.y / 40;
//
//		//troche na sile, ale to sie poprawi :)
//		((WormLayer*)_next)->getBoard(Board::getBoardAsInts());
//
//		if(Board::buffer == 0 && _dialog == 0) {
//			for(auto i : _builders) {
//				if(i->getX() == x && i->getY() == y) {
//					TowerBuilder *tmp = (TowerBuilder*)i;
//
//					Board::buffer = tmp;
//					GameState::info = "Click to build new tower.";
//
//					return;
//				}
//			}
//
//			for(auto i : _toDraw) {
//				if(i != 0 && i->getX() == x && i->getY() == y) {
//					std::cout << "I dare you, I double dare you!" << std::endl;
//
//					Board::buffer = i;
//					_dialog = new Dialog(((Tower*)i)->getLevel() < 3, x, y);
//
//					return;
//				}
//			}
//		}
//
//		if(Board::buffer != 0 && Board::buffer->getName() == "towerBuilder") {
//			if(Board::board[y][x] == 0) {
//				TowerBuilder *b = (TowerBuilder*)Board::buffer;
//
//				if(GameState::money > b->getCost(0)) {
//
//					Tower* t = (Tower*)b->secondClick(x, y);
//
//					Board::board[y][x] = t;
//					_toDraw.push_back(t);
//
//					GameState::money -= b->getCost(0);
//					std::cout << "Yep, you got: $" << GameState::money << std::endl;
//					GameState::info = "New tower built ($ " + toString(b->getCost(0)) + ").";
//
//				}
//				else {
//					std::cout << "Not enough money, sorry" << std::endl;
//					GameState::info = "Not enough money ($ " + toString(b->getCost(0)) + " required).";
//				}
//
//				Board::buffer = 0;
//			}
//		}
//		else if(Board::buffer != 0 && Board::buffer->getName() == "tower") {
//			Tower* tmp = (Tower*)Board::buffer;
//			int level = tmp->getLevel();
//			int number = tmp->getNumber();
//
//			if(y == tmp->getY() + 1) {
//				if(x < tmp->getX()) {
//					if(level >= 3) {
//						std::cout << "No more leveling, man!" << std::endl;
//						GameState::info = "Max. level reached.";
//						Board::buffer = 0;
//					}
//					else {
//						std::cout << "Level it up for god's sake!" << std::endl;
//						int nextLevelCost = TowerBuilder(number).getCost(level);
//
//						if(GameState::money >= nextLevelCost) {
//							GameState::money -= nextLevelCost;
//							tmp->levelUp();
//							GameState::info = "New level set: " + toString(level + 1);
//						}
//						else {
//							GameState::info = "Not enough money \n($ " + toString(nextLevelCost) + " required).";
//							std::cout << "Sorry, bro, no money." << std::endl;
//						}
//						Board::buffer = 0;
//
//					}
//				}
//				else if(x == tmp->getX()) {
//					std::cout << "Sell it, sell this shit!" << std::endl;
//					int levelCost = TowerBuilder(number).getSellingCost(level);
//					std::cout << levelCost << std::endl;
//					GameState::money += levelCost;
//
//					delete Board::board[y][x];
//
//					int off = 0;
//					while(off < _toDraw.size()) {
//						if(_toDraw[off] != 0 && _toDraw[off]->getX() == x && _toDraw[off]->getY() == y - 1) {
//							break;
//						}
//						++off;
//					}
//
//					_toDraw.erase(_toDraw.begin() + off);
//
//					std::cout << "Yep, you got: $" << GameState::money << std::endl;
//					GameState::info = "Tower sold ($ " + toString(levelCost) + ").";
//					Board::buffer = 0;
//
//				}
//				else {
//					Board::buffer = 0;
//				}
////
//			}
//
//			if(_dialog != 0) {
//				Board::buffer = 0;
//				delete _dialog;
//				_dialog = 0;
//			}
//		}
//
//		break;
//
//	}
//}
//
//void TowerLayer::draw() {
//	if(_next != 0) {
//		_next->draw();
//	}
//
//	int tx, ty;
//
//	for(auto i : _builders) {
//		tx = i->getX();
//		ty = i->getY();
//
//		sf::Sprite sprite;
//		sprite.setTexture(*(GameState::textures["towers"]));
//		sprite.setTextureRect(i->getSprite());
//		sprite.setPosition(tx * Board::fieldW, ty * Board::fieldH);
//
//		_window->draw(sprite);
//	}
//
//	for(auto i : _toDraw) {
//		if(i != 0) {
//			tx = i->getX();
//			ty = i->getY();
//
//			sf::Sprite sprite;
//			sprite.setTexture(*(GameState::textures["towers"]));
//			sprite.setTextureRect(i->getSprite());
//			sprite.setPosition(tx * Board::fieldW, ty * Board::fieldH);
//
//			_window->draw(sprite);
//		}
//	}
//
//	// dialog, draw dialog!
//	if(_dialog != 0) {
//		int x = _dialog->getX();
//		int y = _dialog->getY();
//		bool opt = _dialog->getOptions();
//
//		sf::Sprite sprite;
//		sprite.setTexture(*(GameState::textures["dialog"]));
//		if(_dialog->getOptions()) {
//			sprite.setTextureRect(sf::IntRect(0, 0, 120, 40));
//		}
//		else {
//			sprite.setTextureRect(sf::IntRect(0, 40, 120, 40));
//		}
//		sprite.setPosition((x - 1) * Board::fieldW, (y + 1) * Board::fieldH);
//
//		_window->draw(sprite);
//	}
//}

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

	GameState::textures["towers"] = new sf::Texture();
	GameState::textures["towers"]->loadFromFile("graphics/towers.png");

	GameState::textures["dialog"] = new sf::Texture();
	GameState::textures["dialog"]->loadFromFile("graphics/dialog.png");

	_active = sf::RectangleShape(sf::Vector2f(40, 40));
	_active.setOutlineColor(sf::Color(255, 255, 255, 100));
	_active.setOutlineThickness(1);
	_active.setFillColor(sf::Color::Transparent);
}

void TowerLayer::parseEvent(sf::Event &event) {
	if(_next != 0) {
		_next->parseEvent(event);
	}

	int x, y;


	switch(event.type) {
	case sf::Event::MouseButtonPressed:
		x = event.mouseButton.x / 40;
		y = event.mouseButton.y / 40;

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
					std::cout << "I dare you, I double dare you!" << std::endl;

					Board::buffer = i;
					_dialog = new Dialog(((Tower*)i)->getLevel() < 3, x, y);

					return;
				}
			}
		}

		if(Board::buffer != 0 && Board::buffer->getName() == "towerBuilder") {
			if(Board::board[y][x] == 0) {
				TowerBuilder *b = (TowerBuilder*)Board::buffer;

				if(GameState::money > b->getCost(0)) {

					Tower* t = (Tower*)b->secondClick(x, y);

					Board::board[y][x] = t;

					_toDraw.push_back(t);

					GameState::money -= b->getCost(0);
					std::cout << "Yep, you got: $" << GameState::money << std::endl;
					GameState::info = "New tower built ($ " + toString(b->getCost(0)) + ").";
					((WormLayer*)_next)->setPath(Board::getBoardAsInts());
				}
				else {
					std::cout << "Not enough money, sorry" << std::endl;
					GameState::info = "Not enough money ($ " + toString(b->getCost(0)) + " required).";
				}

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
						std::cout << "No more leveling, man!" << std::endl;
						GameState::info = "Max. level reached.";
						Board::buffer = 0;
					}
					else {
						std::cout << "Level it up for god's sake!" << std::endl;
						int nextLevelCost = TowerBuilder(number).getCost(level);

						if(GameState::money >= nextLevelCost) {
							GameState::money -= nextLevelCost;
							tmp->levelUp();
							GameState::info = "New level set: " + toString(level + 1);
						}
						else {
							GameState::info = "Not enough money \n($ " + toString(nextLevelCost) + " required).";
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

//					if(Board::board[y][x])
//						delete Board::board[y][x];
//					Board::board[y][x]=(Clickable*)nullptr;
//					Board::board[y][x+1]=Board::board[y][x];

//					Board::board[2][1]=0;
//
//					std::cout << "x: " << x << " y: " <<y << "board[2][1]: " << Board::board[2][1]<<std::endl;
//
//					auto b = Board::getBoardAsInts();
//						for(auto i : b) {
//							for(auto j : i) {
//								std::cout << j << " ";
//							}
//							std::cout << std::endl;
//						}

					int off = 0;
					while(off < _toDraw.size()) {
						if(_toDraw[off] != 0 && _toDraw[off]->getX() == x && _toDraw[off]->getY() == y - 1) {
							break;
						}
						++off;
					}

					_toDraw.erase(_toDraw.begin() + off);

					std::cout << "Yep, you got: $" << GameState::money << std::endl;
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
		//troche na sile, ale to sie poprawi :)
				//((WormLayer*)_next)->getBoard(Board::getBoardAsInts());
		break;

	case sf::Event::MouseMoved:
		int x = event.mouseMove.x / 40;
		int y = event.mouseMove.y / 40;

		if(x > 14) {
			_active.setPosition(-100, -100);
			break;
		}

		_active.setPosition(x * 40, y * 40);
		_active.setTexture(GameState::textures["towers"]);
		_active.setTextureRect(sf::IntRect(0, 0, 40, 40));
		if(Board::buffer != 0 && Board::buffer->getName() == "towerBuilder"){
			auto tmp=Board::getBoardAsInts();
			tmp[y][x]=1;
			if(((WormLayer*)_next)->pathExists(tmp)){
				_active.setOutlineColor(sf::Color(255, 255, 255, 100));
			} else {
				_active.setOutlineColor(sf::Color(255, 0, 0, 125));
			}
		} else {
			if(Board::board[y][x]) {
				_active.setOutlineColor(sf::Color(255, 0, 0, 125));
			}
			else {
				_active.setOutlineColor(sf::Color(255, 255, 255, 100));
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
	if(_dialog != 0) {
		int x = _dialog->getX();
		int y = _dialog->getY();
		bool opt = _dialog->getOptions();

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

	_window->draw(_active);
}
