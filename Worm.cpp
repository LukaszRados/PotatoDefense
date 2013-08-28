#include "Worm.hpp"

sf::Texture Worm::_texture;

Worm::Worm(int type){
	_sprite=getSprite(type);
	_type=type;
	_dir=sf::Vector2<float>(1,0);

	// putting worm at entrance
	_pos=sf::Vector2<float>(20,Board::height/2*40+20);
	_lastX=0;
	_lastY=Board::height/2;
	_sprite.setPosition(_pos-sf::Vector2<float>(10,10));
	switch(type){
	case 1:
		_max_health=_health=100;
		_value=100;
		_v=0.5;
		_flying=false;
		break;
	default:
		break;
	}
}

bool Worm::dmg(int attack){
	if(attack>=_health)
		_health-=attack;
	else _health=0;

	if(!_health) //smierc
		_alive=false;
	return _alive;
}

void Worm::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	int w=25;
	int h=3;

	sf::Vector2f bar_pos(_pos.x-w/2,_pos.y-15);

	sf::RectangleShape wholeHealth(sf::Vector2f(w,h));
	wholeHealth.setFillColor(sf::Color(255,0,0));
	wholeHealth.setPosition(bar_pos);

	int hp=((float)_health/(float)_max_health*(float)w);



	sf::RectangleShape health(sf::Vector2f(hp,h));
	health.setFillColor(sf::Color(0,255,0));
	health.setPosition(bar_pos);

	target.draw(wholeHealth);
	target.draw(health);
	target.draw(_sprite);
}


bool Worm::go(int time, std::vector<std::vector<int> > path){
	int x=((int)_pos.x)/40;
	int y=((int)_pos.y)/40;
//	if((_lastX != x || _lastY != y) && path[y][x]==-1){
//		_dir=-_dir;
//		_lastX=x;
//		_lastY=y;
//	} else
	if(_lastX==x && _lastY==y){
		//_dir=
	}


	if(len(_pos-sf::Vector2f(x*40+20,y*40+20)) < 1){
		if(_lastX != x || _lastY != y){
			_lastX=x;
			_lastY=y;

			//if(x>10)
			{
				std::cout << "x: " << x << " y: " << y << " dist: " << path[y][x] << std::endl;
			}

//			if(path[y][x]==-1){
//
//			}
			int dist = path[y][x]; // current distance from exit

			bool next=false;

			if(x > 0 && path[y][x-1] > 0 && path[y][x-1] < dist){
				_dir=sf::Vector2f((x-1)*40+20,(y)*40+20)-_pos;
				next=true;
			}


			std::srand((unsigned int)std::time(NULL));

			if(path[y][x+1] > 0 && path[y][x+1] < dist){
				if(next){
					if(rand() % 2)
						_dir=sf::Vector2f((x+1)*40+20,(y)*40+20)-_pos;
				} else {
					_dir=sf::Vector2f((x+1)*40+20,(y)*40+20)-_pos;
					next=true;
				}
			}


			if(path[y-1][x] > 0 && path[y-1][x] < dist){
				if(next){
					if(rand() % 2)
						_dir=sf::Vector2f((x)*40+20,(y-1)*40+20)-_pos;
				} else {
					_dir=sf::Vector2f((x)*40+20,(y-1)*40+20)-_pos;
					next=true;
				}
			}



			if(path[y+1][x] > 0 && path[y+1][x] < dist){
				if(next){
					if(rand() % 2)
						_dir=sf::Vector2f((x)*40+20,(y+1)*40+20)-_pos;
				} else {
					_dir=sf::Vector2f((x)*40+20,(y+1)*40+20)-_pos;
					next=true;
				}
			}

			_dir/=len(_dir);
		}

	}



	//std::cout << "_dir: " << _dir.x << " " << _dir.y << std::endl;
	// moving the worm
	sf::Vector2f tmp(_dir);
	tmp.x*=_v*time/20;
	tmp.y*=_v*time/20;

	_pos+=tmp;

	_sprite.setPosition(_pos-sf::Vector2<float>(10,10));
//	std::cout << x << " " << y << std::endl;



	return path[y][x]==1;
}

void Worm::loadTexture(){
	_texture.loadFromFile("graphics/bug.png");
}

sf::Sprite Worm::getSprite(int type){
	return sf::Sprite(_texture);
}

