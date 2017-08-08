#include <cstdlib>
#include "board.h"

using namespace std;

int height = 25;
int width = 79;

Board::Board(){
  	display = new char*[height];
  	for (int i = 0; i < height; i++){
  		display[i] = new char[width];
	}
  	for (int x = 0; x < height; x++){
   	for (int y = 0; y < width; y++){
    		display[x][y] = ' ';
      }
  	}
}

// change the char at (h,w)
void Board::notify(int h, int w, char ch) {
  	display[h][w] = ch;
}

Board::~Board(){
	int i=0;
	while(i < height){
      delete [] display[i];
		i++;
   }
   delete [] display;
}

ostream &operator<<(ostream &out, const Board &b) {
   for(int x = 0; x < height; x++){
      if(x != 0){
	 		out << endl;
		}
      for (int y = 0; y < width; y++) {
            out << b.display[x][y];
      }
	}
  	return out;
}

ostream &operator<<(ostream &out, const Board *b) {
	refresh();
	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			char ch = b->display[i][j];
			if(ch == '@'){
				attron(A_BOLD);
			}
			if(ch == '\\'){
				attron(A_BOLD);
				attron(COLOR_PAIR(3));
			}
			if(ch == 'G'){
				attron(COLOR_PAIR(1));
			}
			if(ch == 'P'){
				attron(COLOR_PAIR(2));
			}
				mvaddch(i,j,ch);
				refresh();
			if(ch == '@'){
				attroff(A_BOLD);
			}
			if(ch == '\\')	{
				attroff(A_BOLD);
				attroff(COLOR_PAIR(3));
			}
			if(ch == 'G'){
				attroff(COLOR_PAIR(1));
			}
			if(ch == 'P'){
				attroff(COLOR_PAIR(2));
			}	
		}
	}
	return out;
}
