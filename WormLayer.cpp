#include "WormLayer.hpp"

 std::vector<std::vector<int> > WormLayer::_path;
 std::list<Worm> WormLayer::worms;
std::vector<std::vector<int> > WormLayer::enemies;

bool WormLayer::isFree(int x, int y){
	for(auto i : worms){
		int _x=int(i._pos.x) / 40;
		int _y=int(i._pos.y) / 40;
		if(_x==x && _y==y && !i.isFlying())
			return false;
	}

	return true;
}

WormLayer::WormLayer(sf::RenderWindow *w):Layer(w){
	_time.restart();
	GameState::waveTime.restart();
	_moreEnemies=true;
	_waveOn=true;
	setPath(Board::getBoardAsInts());
	if(GameState::music) {
		GameState::sounds["gong"]->setVolume(75);
		GameState::sounds["gong"]->play();
	}

	enemies = {		// 30 sec
		{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,
		 0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,-1}, //wave 1

		{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,
		 0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,
		 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,2,-1}, //wave 2

		{0,3,0,2,0,3,0,2,0,3,0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,
		 3,0,0,0,0,3,0,2,0,4,0,1,1,1,1,1,1,1,2,2,2,1,1,0,0,
		 2,3,2,3,2,1,1,1,1,1,1,1,1,2,2,2,1,1,2,1,1,0,3,3,3,0,1,0,1,0,
		 1,0,1,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,-1}, //wave 3

		{5,5,5,5,5,5,5,5,1,1,1,1,0,0,0,0,0,0,2,2,2,0,0,1,1,1,4,4,0,3,
		 2,2,2,2,5,5,5,5,2,2,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		 0,0,0,0,0,5,5,5,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,
		 4,4,4,4,0,0,0,0,0,5,5,5,1,1,1,1,2,2,2,2,2,2,2,2,3,3,2,2,2,2,
		 0,0,0,6,0,0,0,0,0,6,0,0,6,0,5,5,5,5,0,0,6,-1}, //wave 4

		{4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		-1}, //wave 5 - death wave xD

		{0,7,7,7,7,7,7,0,0,0,0,4,4,4,4,4,4,3,3,3,3,3,4,4,4,3,3,3,0,0,
		 6,6,6,6,6,6,0,0,0,3,5,5,5,5,5,5,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,-1
		}, //wave 6

		{6,7,6,7,6,7,6,7,6,7,6,7,7,7,7,7,7,0,0,0,0,6,6,6,6,6,7,7,7,7,
		 4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,7,7,7,6,6,6,-1}, //wave 7

		{0,8,-1} //final


	};
}

WormLayer::~WormLayer() {
	if(_next != 0) {
		delete _next;
	}

	worms.clear();

}

void WormLayer::parseEvent(sf::Event &event){
	if(_next!=nullptr){
		_next->parseEvent(event);
	}
}

void WormLayer::draw(){
	if(_next != 0) {
			_next->draw();
		}

	//rysowanie robakow
	for(auto & i:worms){
		sf::Sprite spr = i.getSprite(i.getType());
		spr.setPosition(i.getPos());
		i.setSprite(spr);

		_window->draw(i);
	}


	if(!_moreEnemies && worms.empty() &&
			(int)_time.getElapsedTime().asSeconds() <= GameState::secondsBetweenWaves && GameState::wave < GameState::maxWaves){

			sf::Sprite sprite;
			sprite.setTexture(*(GameState::textures["nextIn"]));
			sprite.setTextureRect(sf::IntRect(0, 0, 200, 55));
			sprite.setPosition(200, 240);
			_window->draw(sprite);

			sprite.setTexture(*(GameState::textures["nextNo"]));
			sprite.setTextureRect(sf::IntRect((GameState::secondsBetweenWaves-(int)_time.getElapsedTime().asSeconds()) * 100, 0, 100, 100));
			sprite.setPosition(250, 280);
			_window->draw(sprite);
	}

}

void WormLayer::update(){
	if( _next != 0 )
		_next->update();

	switch(GameState::state){
	case Paused:
		_time.pause();
		break;


	case Game:
			//*********** Restart timers *****************//
			if(_time.isPaused())
				_time.start();

			//*********************************************//
		// adding new worms
		if(_moreEnemies){
			int i =(int)(GameState::waveTime.getElapsedTime().asSeconds());
			int nextWorm=enemies[GameState::wave-1][i];
			enemies[GameState::wave-1][i]=0; // for not adding same worm more than once
			if(nextWorm>0){
				worms.push_back(Worm(nextWorm));

			} else if(nextWorm==-1){
				_moreEnemies=false;
			}
		}


		worms.remove_if(Worm::isDead);

		if(!_moreEnemies && worms.empty()){
			if(_waveOn){
				_waveOn=false;
				_time.restart();
			} else {

				if(GameState::wave==GameState::maxWaves){
					GameState::state=Win;
					return;
				}

				int seconds=(int)_time.getElapsedTime().asSeconds();
				if(seconds >= GameState::secondsBetweenWaves){
					GameState::wave++;
					GameState::waveTime.restart();
					if(GameState::music) {
						GameState::sounds["gong"]->play();
					}
					_time.restart();
					_moreEnemies=true;
					_waveOn=true;
					worms.clear();
					Board::save();
				}

			}

			return; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}
		for(auto & worm : worms){
			//printPath(_path);
			if(worm._alive && worm.go(_time.getElapsedTime().asSeconds()*20, _path)){
				if(GameState::lifes > 0) GameState::lifes-=worm._lifes;
				worm.dmg(worm._health);
			}

		}
//		worms.remove_if(Worm::isDead); // forget the dead


		//to estimate time since last move
		_time.restart();
		break;
	case Win:
	case GameOver:
		break;
	} // end switch


}

void WormLayer::printPath(std::vector<std::vector<int> >  path){
	std::cout << std::endl;
	for(auto i : path){
		for(auto j : i)
			std::cout << j << " ";
		std::cout << std::endl;
	}
}



std::vector<std::vector<int> > WormLayer::findPath(std::vector<std::vector<int> >  board){


	auto path=board;

	for(auto i=0;i<_s;i++)
		for(auto j=0;j<_s;j++){
			switch(path[i][j]){
			case 1:
				path[i][j]=-1;
				break;
			case 2:
				path[i][j]=0;
				break;

			case 3:
				path[i][j]=1;
				break;
			}

		}
	//printPath(path);
	bool change=true;
	while(change){
		change=false;
		for(auto y=1;y<_s-1;y++)
			for(auto x=1;x<_s-1;x++){

				if(path[x][y]<0) continue;
				int tmp=path[x][y];
				if(path[x+1][y]>0) //prawo jeśli nie ma ściany, ale został odwiedzony
					if(path[x+1][y]+1<path[x][y] || path[x][y]==0) //i jeśli z tamtej drogi jest krócej do aktualnej,
					//lub aktualna jest nieodwiedzona
				path[x][y]=path[x+1][y]+1; //oznacza tutaj odległość poprzedniej+1

				if(path[x-1][y]>0) //lewo
					if(path[x-1][y]+1<path[x][y] || path[x][y]==0)
					path[x][y]=path[x-1][y]+1;

				if(path[x][y+1]>0) //dół
					if(path[x][y+1]+1<path[x][y] || path[x][y]==0)
					path[x][y]=path[x][y+1]+1;

				if(path[x][y-1]>0) //góra
					if(path[x][y-1]+1<path[x][y] || path[x][y]==0)
					path[x][y]=path[x][y-1]+1;

				if(tmp!=path[x][y]) change=true;
			}
	}

	return path;
}

void WormLayer::setPath(std::vector<std::vector<int> >  ints){
	_path=findPath(ints);
	_path[Board::height/2][0]=_path[Board::height/2][1]+1;
	//printPath(_path);
}

bool WormLayer::pathExists(std::vector<std::vector<int> > ints){
	auto tmp=findPath(ints);

	return (tmp[7][1] > 0); //jesli tam jest <0 to znaczy ze nie ma sciezki
}


