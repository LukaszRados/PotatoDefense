#include "WormLayer.hpp"

 std::vector<std::vector<int> > WormLayer::_path;
 std::list<Worm> WormLayer::worms;

WormLayer::WormLayer(sf::RenderWindow *w):Layer(w){
	_next= new BgLayer(w);
	Worm::loadTexture();
	_time.restart();
//
//	for(int i=0;i<_s*_dens;i++)
//		_board.push_back(std::vector<int>(_s*_dens));


}

void WormLayer::parseEvent(sf::Event &event){
	if(_next!=nullptr){
		_next->parseEvent(event);
	}

	worms.remove_if(Worm::isDead);

	for(auto worm : worms){
		if(move(worm,int(_time.getElapsedTime().asMilliseconds()))){
			//odbieranie nam szans itp
		}
	}
	//zeby przy nastepnym przesuwaniu wiadomo bylo o ile przesunac
	_time.restart();


}

void WormLayer::draw(){
	_next->draw();

	//rysowanie robakow
	for(auto i:worms){
		//_window->draw(i);
	}
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
	// changing names
	sf::Vector2<float> & _pos=worm._pos;
	sf::Vector2<float> & _dir=worm._dir;

	std::srand((unsigned int)std::time(NULL));
		//updating direction
		if(((((int)_pos.x)/20) % 2) && ((((int)_pos.x)/20) % 2)){
			int x=_pos.x/40;
			int y=_pos.y/40; // changing _pos to Board coords

			int dist=WormLayer::_path[y][x]; //current distance to exit
			int next=0;

			if(x>0 && WormLayer::_path[y][x-1]<dist){
				next=WormLayer::_path[y][x-1]; //go to the left
				_dir=sf::Vector2<float>(-1,0);
			}

			if(WormLayer::_path[y][x+1]<dist){ //go to the right
				 if(next && next==WormLayer::_path[y][x+1] && std::rand() % 2){
					 _dir=sf::Vector2<float>(1,0);
				 } else {
					 _dir=sf::Vector2<float>(1,0);
					 next=WormLayer::_path[y][x+1];
				 }
			}
			if(WormLayer::_path[y-1][x]<dist){ //go to the top
				 if(next && next==WormLayer::_path[y-1][x] && std::rand() % 2){
					 _dir=sf::Vector2<float>(0,-1);
				 } else {
					 _dir=sf::Vector2<float>(0,-1);
					 next=WormLayer::_path[y-1][x];
				 }
			}
			if(WormLayer::_path[y+1][x]<dist){ //go to the bottom
				 if(next && next==WormLayer::_path[y+1][x] && std::rand() % 2){
					 _dir=sf::Vector2<float>(0,1);
				 } else {
					 _dir=sf::Vector2<float>(0,1);
					 next=WormLayer::_path[y+1][x];
				 }
			}
			//without else after each case, so the worm could change its mind where to go :)
		}
		// end of updating direction

		sf::Vector2f tmp(_dir);
		tmp*=worm._v*time;
		_pos+=tmp;


		return WormLayer::_path[_pos.y/40][_pos.y/40]==1;
}
