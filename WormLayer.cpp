#include "WormLayer.hpp"

WormLayer::WormLayer(sf::RenderWindow *w):Layer(w){
	_next= new BgLayer(w);



	for(int i=0;i<_s*_dens;i++)
		_board.push_back(std::vector<int>(_s*_dens));

	getBoard(Board::getBoardAsInts());
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


void WormLayer::printBoard(){
	std::cout << std::endl;
	for(auto i : _board){
		for(auto j : i)
			std::cout << j << " ";
		std::cout << std::endl;
	}
}

void WormLayer::fillBoard(int val, int x, int y){
	for(int i=0;i<_dens;i++)
		for(int j=0;j<_dens;j++){
			_board[x*_dens+i][y*_dens+j]=val;
		}
}

void WormLayer::getBoard(std::vector<std::vector<int> >  ints){
	for(int i=0;i<_s;i++)
		for(int j=0;j<_s;j++){
			fillBoard(ints[i][j], i, j);
		}


	//test
	printBoard();
}
