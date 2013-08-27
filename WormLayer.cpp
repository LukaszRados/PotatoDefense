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
		if(worm.go(int(_time.getElapsedTime().asMilliseconds()))){
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
		_window->draw(i);
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
