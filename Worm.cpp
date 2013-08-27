#include "Worm.hpp"

sf::Texture Worm::_texture;

Worm::Worm(int type){
	_sprite=getSprite(type);
	_type=type;
	_dir=sf::Vector2<float>(1,0);

	// putting worm at entrance
	_pos=sf::Vector2<float>(Board::height/2*40+20,20);
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
	sf::Sprite tmp=_sprite;
	tmp.setPosition(_pos-sf::Vector2<float>(20,20));
	target.draw(tmp);
}


bool Worm::go(int time){
//	std::srand((unsigned int)std::time(NULL));
//	//updating direction
//	if((_pos.x/20) % 2 && (_pos.y/20) % 2){
//		int x=_pos.x/40;
//		int y=_pos.y/40; // changing _pos to Board coords
//
//		int dist=WormLayer::_path[y][x]; //current distance to exit
//		int next=0;
//
//		if(x>0 && WormLayer::_path[y][x-1]<dist){
//			next=WormLayer::_path[y][x-1]; //go to the left
//			_dir=sf::Vector2<int>(-1,0);
//		}
//
//		if(WormLayer::_path[y][x+1]<dist){ //go to the right
//			 if(next && next==WormLayer::_path[y][x+1] && std::rand() % 2){
//				 _dir=sf::Vector2<int>(1,0);
//			 } else {
//				 _dir=sf::Vector2<int>(1,0);
//				 next=WormLayer::_path[y][x+1];
//			 }
//		}
//		if(WormLayer::_path[y-1][x]<dist){ //go to the top
//			 if(next && next==WormLayer::_path[y-1][x] && std::rand() % 2){
//				 _dir=sf::Vector2<int>(0,-1);
//			 } else {
//				 _dir=sf::Vector2<int>(0,-1);
//				 next=WormLayer::_path[y-1][x];
//			 }
//		}
//		if(WormLayer::_path[y+1][x]<dist){ //go to the bottom
//			 if(next && next==WormLayer::_path[y+1][x] && std::rand() % 2){
//				 _dir=sf::Vector2<int>(0,1);
//			 } else {
//				 _dir=sf::Vector2<int>(0,1);
//				 next=WormLayer::_path[y+1][x];
//			 }
//		}
//		//without else after each case, so the worm could change its mind where to go :)
//	}
//	// end of updating direction
//
//	sf::Vector2f tmp((float)_dir.x,(float)_dir.y);
//	tmp*=_v*time;
//	_pos+=sf::Vector2i((int)tmp.x,(int)tmp.y);
//
//	return WormLayer::_path[_pos.y/40][_pos.y/40]==1;
}

void Worm::loadTexture(){
	_texture.loadFromFile("graphics/bug.png");
}

sf::Sprite Worm::getSprite(int type){
	return sf::Sprite(_texture);
}
