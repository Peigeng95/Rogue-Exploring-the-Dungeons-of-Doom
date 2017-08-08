#include "cell.h"
#include "room.h"

using namespace std;

void Cell::notifyDisplay(){
   int x = this->h;
   int y = this->w;
   char symbol = this->ch;
   b->notify(x, y, symbol);
}

//ctor
Cell::Cell():b(NULL), numNeigh(0), alSet(true){
	int i=0;
	while(i<4){
		neigh[i] = NULL;
		i++;
	}
}

//ctor with ch and board
Cell::Cell(char ch, Board *b): ch(ch), b(b), numNeigh(0), alSet(false){
	int i=0;
	while(i<4){
		neigh[i] = NULL;
		i++;
	}
}

//arrange a room
void Cell::arrangeRoom(Room &rm){
	if(this->alSet == false){
		rm.addFloor(this);
		this->alSet = true;
	}
	for(int i = 0; i < numNeigh; i++){
		if(this->neigh[i]->alSet == false){
			this->neigh[i]->arrangeRoom(rm);
			this->neigh[i]->alSet = true;
		}
	}
}

//addNeightbour
void Cell::addNeighbour(Cell *c){
	if(numNeigh < 4) {
		neigh[numNeigh] = c;
		numNeigh++;
	}
}

//bool
bool Cell::Set(){
	return this->alSet;
}


//get width
int Cell::getW(){
	return this->w;
}

//get height
int Cell::getH(){
	return this->h;
}

//get current ch
char Cell::getSymbol(){
	return ch; 
}

//get prev ch
char Cell::getPrev() {
	return this->prev;
}

//set prev ch to
void Cell::setPrev(char ch) {
	this->prev = ch;
}

//set height and width
void Cell::setCoords(const int h, const int w) {
	this->h = h;
	this->w = w;
	this->notifyDisplay(); //change the board
}


void Cell::setDisplay(Board * b) {
	this->b = b;
}

//dtor
Cell::~Cell(){}
