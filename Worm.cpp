#include "Worm.hpp"

Worm::Worm(int type){
	_sprite=getSprite(type);
	_type=type;
	_dir=sf::Vector2<float>(1,0);
	_rotate = 1;

	// putting worm at entrance
	_pos=sf::Vector2<float>(20,Board::height/2*40+20);
	_lastX=0;
	_lastY=Board::height/2;
	_sprite.setPosition(_pos-sf::Vector2<float>(10,10));
	switch(type){
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		_max_health=_health=100;
		_value=100;
		_v=0.5;
		_flying=false;
		break;
	default:
		break;
	}
	_time.restart();
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

	if(len(_pos-sf::Vector2f(x*40+20,y*40+20)) < 1){
		if(_lastX != x || _lastY != y){
			_lastX=x;
			_lastY=y;

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

			// new rotate here
			// atan(_dir.y / _dir.x) * 180 / 3.14
		}

	}



	// moving the worm
	sf::Vector2f tmp(_dir);
	tmp.x*=_v*time/20;
	tmp.y*=_v*time/20;

	_pos+=tmp;

	_sprite.setPosition(_pos-sf::Vector2<float>(10,10));



	return path[y][x]==1;
}

sf::Sprite Worm::getSprite(int type){
	sf::Sprite tmp;
	int t = ((int)(GameState::waveTime.getElapsedTime().asMilliseconds()) / 200) % 2;

	tmp.setTexture(*(GameState::textures["bugs"]));
	tmp.setTextureRect(sf::IntRect((type - 1) * 40, t * 40, 40, 40));

	tmp.setOrigin(20, 20);
	tmp.setRotation(_rotate * 90);

	return tmp;
}

