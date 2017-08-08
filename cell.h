#ifndef __CELL_H__
#define __CELL_H__

#include <string>
#include <iostream>
#include "board.h"

class Room;

class Cell {
   protected:
   	int h, w; //height and width
   	char ch, prev; // prev char and current char
   	Board * b; //board
		int numNeigh;
		Cell *neigh[4];
		bool alSet;
   	void notifyDisplay();
   public:
   	Cell();
   	Cell(char, Board *);
		void arrangeRoom(Room &);
		void addNeighbour(Cell *);
		bool Set();
   	int getW();
   	int getH();
   	char getSymbol();
   	char getPrev();
   	void setPrev(char);
   	void setCoords(const int h, const int w);
   	void setDisplay(Board * b);
   	virtual ~Cell();
};
#endif
