#ifndef __BOARD_H__
#define __BOARD_H__

#include <ncurses.h>
#include <iostream>

extern int width;
extern int height;

class Board {
	char **display;
 	public:
  		Board();
	 	void notify(int h, int w, char ch); // change the char at (h,w)
  		~Board();
  	friend std::ostream &operator<<(std::ostream &out, const Board &td);
  	friend std::ostream &operator<<(std::ostream &out, const Board *td);
};
#endif
