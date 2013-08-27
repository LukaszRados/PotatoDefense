#include "Worm.hpp"

sf::Texture Worm::_texture;

Worm::Worm(int type){
	_sprite=getSprite(type);

	switch(type){
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

}

sf::Sprite Worm::getSprite(int type){
	return sf::Sprite();
}
