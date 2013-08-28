#include "WormLayer.hpp"

 std::vector<std::vector<int> > WormLayer::_path;
 std::list<Worm> WormLayer::worms;
std::vector<std::vector<int> > WormLayer::enemies={
		{1,0,1,0,1,0,1,0,1,0,1,-1,1,0,0,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,-1} //wave 1
};


WormLayer::WormLayer(sf::RenderWindow *w):Layer(w){
	_next= new BgLayer(w);
	Worm::loadTexture();
	_time.restart();
	GameState::waveTime.restart();
	moreEnemies=true;

	setPath(Board::getBoardAsInts());
//
//	for(int i=0;i<_s*_dens;i++)
//		_board.push_back(std::vector<int>(_s*_dens));


}

void WormLayer::parseEvent(sf::Event &event){
	if(_next!=nullptr){
		_next->parseEvent(event);
	}



}

void WormLayer::draw(){
	_next->draw();

	//rysowanie robakow
	for(auto & i:worms){
		_window->draw(i);
	}
}

void WormLayer::update(){
	if( _next != 0 )
		_next->update();

	// adding new worms
//	std:: cout <<enemies[GameState::wave-1][(int)GameState::waveTime.getElapsedTime().asSeconds()] << std::endl;

	if(moreEnemies){
		int i =(int)(GameState::waveTime.getElapsedTime().asSeconds()*2);

		//std::cout << "more enemies index: "<< i  << std::endl;

		int nextWorm=enemies[GameState::wave-1][i];
		enemies[GameState::wave-1][i]=0; // for not adding same worm more than once
		if(nextWorm>0){
			worms.push_back(Worm(nextWorm));
			//std::cout << nextWorm << " ";
		} else if(nextWorm==-1){
			moreEnemies=false;
		}
	}




	for(auto & worm : worms){
		//printPath(_path);
		if(worm._alive && worm.go(_time.getElapsedTime().asMilliseconds(), _path)){
			GameState::lifes--;
			worm.dmg(worm._health);
		}

	}

//	std::cout << "removing dead " << std::endl;
	worms.remove_if(Worm::isDead); // forget the dead
//	std::cout << "worms count: " << worms.size() << std::endl;
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
	printPath(_path);
}

bool WormLayer::pathExists(std::vector<std::vector<int> > ints){
	auto tmp=findPath(ints);

	return (tmp[7][1] > 0); //jesli tam jest <0 to znaczy ze nie ma sciezki
}


bool WormLayer::move(Worm & worm, int time){
	std::cout << "moving worm "  << std::endl;

	// changing names
	sf::Vector2<float> & _pos=worm._pos;
	sf::Vector2<float> & _dir=worm._dir;

	std::cout << "referencje" << std::endl;

//	std::srand((unsigned int)std::time(NULL));
//		//updating direction
//	//if(((((int)_pos.x)/20) % 2) && ((((int)_pos.x)/20) % 2)){
//	sf::Vector2<float> board_pos(int(_pos.x)/40,int(_pos.y)/40);
//
//	if(len(_pos-board_pos) < 4)
//	{
//			int x=_pos.x/40;
//			int y=_pos.y/40; // changing _pos to Board coords
//
//			int dist=WormLayer::_path[y][x]; //current distance to exit
//			int next=0;
//
//			if(x>0 && WormLayer::_path[y][x-1]<dist){
//				next=WormLayer::_path[y][x-1]; //go to the left
//				_dir=_pos-sf::Vector2<float>((x-1)*40,y*50);
//			}
//
//			if(WormLayer::_path[y][x+1]<dist){ //go to the right
//				 if(next && next==WormLayer::_path[y][x+1] && std::rand() % 2){
//					 _dir=_pos-sf::Vector2<float>((x+1)*40,y*50);
//					 //_dir=sf::Vector2<float>(1,0);
//				 } else {
//					 _dir=_pos-sf::Vector2<float>((x+1)*40,(y)*50);
//					 //_dir=sf::Vector2<float>(1,0);
//					 next=WormLayer::_path[y][x+1];
//				 }
//			}
//			if(WormLayer::_path[y-1][x]<dist){ //go to the top
//				 if(next && next==WormLayer::_path[y-1][x] && std::rand() % 2){
//					 _dir=_pos-sf::Vector2<float>((x)*40,(y-1)*50);
//					 //_dir=sf::Vector2<float>(0,-1);
//				 } else {
//					 _dir=_pos-sf::Vector2<float>((x)*40,(y-1)*50);
//					 //_dir=sf::Vector2<float>(0,-1);
//					 next=WormLayer::_path[y-1][x];
//				 }
//			}
//			if(WormLayer::_path[y+1][x]<dist){ //go to the bottom
//				 if(next && next==WormLayer::_path[y+1][x] && std::rand() % 2){
//					 _dir=_pos-sf::Vector2<float>((x)*40,(y+1)*50);
//					 //_dir=sf::Vector2<float>(0,1);
//				 } else {
//					 _dir=_pos-sf::Vector2<float>((x)*40,(y+1)*50);
//					 //_dir=sf::Vector2<float>(0,1);
//					 next=WormLayer::_path[y+1][x];
//				 }
//			}
//			//without else after each case, so the worm could change its mind where to go :)
//		}
//		// end of updating direction
//
		sf::Vector2f tmp(_dir);
	//	tmp*=(worm._v*time/100);
		_pos+=tmp;


	//	return WormLayer::_path[_pos.y/40][_pos.y/40]==1;
}
