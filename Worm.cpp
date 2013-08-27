#include "Worm.hpp"

sf::Texture Worm::_texture;

Worm::Worm(int type){
	_sprite=getSprite(type);
	_type=type;

	switch(type){
	case 1:
		_dir=sf::Vector2<int>(0,0);
		// putting wrom at entrance
		_pos=sf::Vector2<int>(Board::height/2*40+20,20);

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
}


bool Worm::go(int time){
	return false;
}

void Worm::loadTexture(){
	_texture.loadFromFile("graphics/bug.png");
}

sf::Sprite Worm::getSprite(int type){
	return sf::Sprite(_texture);
}
