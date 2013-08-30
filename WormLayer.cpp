#include "WormLayer.hpp"

 std::vector<std::vector<int> > WormLayer::_path;
 std::list<Worm> WormLayer::worms;
std::vector<std::vector<int> > WormLayer::enemies={
		{1,0,2,0,3,0,4,0,5,0,6,0,7,0,0,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,-1} //wave 1
};

bool WormLayer::isFree(int x, int y){
	for(auto i : worms){
		int _x=int(i._pos.x) / 40;
		int _y=int(i._pos.y) / 40;
		if(_x==x && _y==y)
			return false;
	}

	return true;
}

WormLayer::WormLayer(sf::RenderWindow *w):Layer(w){
	_next= new BgLayer(w);
	_time.restart();
	GameState::waveTime.restart();
	moreEnemies=true;

	setPath(Board::getBoardAsInts());

	GameState::textures["bugs"] = new sf::Texture();
	GameState::textures["bugs"]->loadFromFile("graphics/worms.png");
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

}

void WormLayer::update(){
	if( _next != 0 )
		_next->update();

	// adding new worms


	if(moreEnemies){
		int i =(int)(GameState::waveTime.getElapsedTime().asSeconds());

		int nextWorm=enemies[GameState::wave-1][i];
		enemies[GameState::wave-1][i]=0; // for not adding same worm more than once
		if(nextWorm>0){
			worms.push_back(Worm(nextWorm));
		} else if(nextWorm==-1){
			moreEnemies=false;
		}
	}


	worms.remove_if(Worm::isDead);

	for(auto & worm : worms){
		//printPath(_path);
		if(worm._alive && worm.go(_time.getElapsedTime().asSeconds()*20, _path)){
			GameState::lifes--;
			worm.dmg(worm._health);
		}

	}


	worms.remove_if(Worm::isDead); // forget the dead
	//to estimate time since last move
	_time.restart();
}

WormLayer::~WormLayer(){
	if(_next!=nullptr)
		delete _next;
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


