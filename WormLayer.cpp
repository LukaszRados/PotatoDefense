#include "WormLayer.hpp"

WormLayer::WormLayer(sf::RenderWindow *w):Layer(w){
	_next= new BgLayer(w);


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
}

WormLayer::~WormLayer(){
	if(_next!=nullptr)
		delete _next;
}

//
//void WormLayer::printBoard(std::vector<std::vector<int> > board){
//	std::cout << std::endl;
//	for(auto i : board){
//		for(auto j : i)
//			std::cout << j << " ";
//		std::cout << std::endl;
//	}
//}


void WormLayer::printPath(std::vector<std::vector<int> >  path){
	std::cout << std::endl;
	for(auto i : path){
		for(auto j : i)
			std::cout << j << " ";
		std::cout << std::endl;
	}
}

void WormLayer::fillBoard(std::vector<std::vector<int> >  & board,int val, int x, int y){
	for(int i=0;i<_dens;i++)
		for(int j=0;j<_dens;j++){
			board[x*_dens+i][y*_dens+j]=val;
		}
}



std::vector<std::vector<int> > WormLayer::findPath(std::vector<std::vector<int> >  board){


	auto path=board;

//	std::cout << path[0].size() << " " << _s*_dens<< std::endl;

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
	printPath(path);
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

std::vector<std::vector<int> > WormLayer::getBoard(std::vector<std::vector<int> >  ints){
	std::vector<std::vector<int> > tmp;
	for(int i=0;i<_s*_dens;i++)
		tmp.push_back(std::vector<int>(_s*_dens));

	for(int i=0;i<_s;i++)
		for(int j=0;j<_s;j++){
			fillBoard(tmp,ints[i][j], i, j);
		}
	return tmp;
}

void WormLayer::setPath(std::vector<std::vector<int> >  ints){
	//_path=findPath(getBoard(ints));
	_path=findPath(ints);

	printPath(_path);
}

bool WormLayer::pathExists(std::vector<std::vector<int> > ints){
	auto tmp=findPath(ints);//getBoard(ints));

	return (tmp[7][1]);
}
