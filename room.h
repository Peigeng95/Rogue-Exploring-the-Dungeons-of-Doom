#ifndef __ROOM_H__
#define __ROOM_H__

#include "cell.h"
#include <vector>
#include <cstdlib>
#include <iostream>

class Room {
	std::vector<Cell*> rm;
	public:
		int giveCoords(int &r, int &c);
		bool isFilled();
		void addFloor(Cell*);
		void changePos(const int &pos, Cell *c);
		void cleanRoom();
};	
#endif
