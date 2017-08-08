#include "room.h"

using namespace std;

//random coords
int Room::giveCoords(int &h, int &w){
	int randNum = rand() % rm.size();
	for(;;){
		if (rm[randNum]->getSymbol() == '.'){
			h = rm[randNum]->getH();
			w = rm[randNum]->getW();
			return randNum;
		}
		else randNum = rand() % rm.size();
	}
}

//see if the room is full
bool Room::isFilled(){
	for(unsigned int i = 0; i < rm.size(); i++){
		if(rm[i]->getSymbol() == '.'){
			return false;
		}
		else continue;
	}
	return true;
}

//change position
void Room::changePos(const int &pos, Cell *c) {
	rm[pos] = c;
}

//add one floor
void Room::addFloor(Cell *c){
	rm.push_back(c);
}

//clean all cells
void Room::cleanRoom() {
	rm.clear();
}
