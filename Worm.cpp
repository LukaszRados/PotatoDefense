#include "Worm.hpp"

Worm::Worm(int type){
	_sprite=getSprite(type);
	_type=type;
	_dir=sf::Vector2<float>(1,0);
	_rotate = 1;
	_dist=666; // just to be evil :)
	// putting worm at entrance
	_pos=sf::Vector2<float>(20,Board::height/2*40+20);
	_lastX=0;
	_lastY=Board::height/2;
	_sprite.setPosition(_pos-sf::Vector2<float>(10,10));
	switch(type){
	case 1:
		_max_health=_health=30;
			_value=10;
			_lifes=1;
			_v=1;
			_flying=false;
			break;
	case 2:
		_max_health=_health=300;
			_value=50;
			_lifes=2;
			_v=1;
			_flying=false;
			break;
	case 3:
		_max_health=_health=80;
			_value=40;
			_v=1.5;
			_lifes=1;
			_flying=true;
			break;
	case 4:
		_max_health=_health=200;
			_value=80;
			_v=1.2;
			_lifes=2;
			_flying=true;
			break;
	case 5:
		_max_health=_health=80;
			_value=50;
			_v=3;
			_flying=false;
			_lifes=1;
			break;
	case 6:
		_max_health=_health=2000;
			_value=180;
			_v=0.8;
			_lifes=5;
			_flying=false;
			break;
	case 7:
		_max_health=_health=1000;
		_value=80;
		_lifes=3;
		_v=1.2;
		_flying=false;
		break;
	case 8:
		_max_health=_health=20000;
		_value=0;
		_v=0.8;
		_lifes=20;
		_flying=false;
		_sprite=getSprite(7);
		break;

	default:
		break;
	}
	_time.restart();
}

bool Worm::dmg(int attack){
	_health-=attack;

	if(_health <= 0){ //smierc
		_alive=false;
		_health=0;
	}

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

	target.draw(_sprite);
	target.draw(wholeHealth);
	target.draw(health);
}


bool Worm::go(float time, std::vector<std::vector<int> > path){
	int x=((int)_pos.x)/40;
	int y=((int)_pos.y)/40;

	if(!_flying){
		// in case when tower is put directly in front of worm
		if((_lastX != x || _lastY != y) && path[y][x]==-1){
			_dir=sf::Vector2f((_lastX)*40+20,(_lastY)*40+20)-_pos;
			_dist=path[_lastY][_lastY];

			_lastX=x;
			_lastY=y;
		} else
		if(len(_pos-sf::Vector2f(x*40+20,y*40+20)) < 1){
			if(_lastX != x || _lastY != y){

				_lastX=x;
				_lastY=y;


					_dist = path[y][x]; // current distance from exit

					bool next=false;

					if(x > 0 && path[y][x-1] > 0 && path[y][x-1] < _dist){
						_dir=sf::Vector2f((x-1)*40+20,(y)*40+20)-_pos;
						next=true;
					}


					std::srand((unsigned int)std::time(NULL));

					if(path[y][x+1] > 0 && path[y][x+1] < _dist){
						if(next){
							if(rand() % 2)
								_dir=sf::Vector2f((x+1)*40+20,(y)*40+20)-_pos;
						} else {
							_dir=sf::Vector2f((x+1)*40+20,(y)*40+20)-_pos;
							next=true;
						}
					}


					if(path[y-1][x] > 0 && path[y-1][x] < _dist){
						if(next){
							if(rand() % 2)
								_dir=sf::Vector2f((x)*40+20,(y-1)*40+20)-_pos;
						} else {
							_dir=sf::Vector2f((x)*40+20,(y-1)*40+20)-_pos;
							next=true;
						}
					}



					if(path[y+1][x] > 0 && path[y+1][x] < _dist){
						if(next){
							if(rand() % 2)
								_dir=sf::Vector2f((x)*40+20,(y+1)*40+20)-_pos;
						} else {
							_dir=sf::Vector2f((x)*40+20,(y+1)*40+20)-_pos;
							next=true;
						}
					}
				}




		}

		_dir/=len(_dir);


	} else {
		_dist=Board::height-x;
	}


	// atan(_dir.y / _dir.x) * 180 / 3.14
	if(abs(_dir.x) <= 0.04 && _dir.y > 0.8){
		_rotate=2;
	} else if (abs(_dir.x) <= 0.04 && _dir.y < -0.8){
		_rotate=0;
	}else if (abs(_dir.y) <= 0.04 && _dir.x < -0.8){
		_rotate=3;
	}else if (abs(_dir.y) <= 0.04 && _dir.x > 0.8){
		_rotate=1;
	}

	// moving the worm
	sf::Vector2f tmp(_dir);
	tmp.x*=_v*time;
	tmp.y*=_v*time;

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


float Worm::distance(int x, int y){
	return len(_pos-sf::Vector2f(x*40+20,y*40+20));
}
