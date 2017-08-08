#include <iostream>
#include <sstream>
#include <fstream>
#include "grid.h"
#include <cstdlib>
#include "printfile.h"
#include <ncurses.h>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
	string fileName = "dungeon.txt";
	if (argc > 2) {
		cerr << "Only one file name is required!" << endl;
		return -1;
	}
	else if (argc == 2) {
		stringstream sin(argv[1]);
		sin >> fileName;
	}
	srand(time(NULL));
	string mode;
 	Print::printfile("choosemode.txt");
	cin >> mode;
	if (fileName == "dungeon.txt") {
		if (mode == "command")
			Grid::commandPlay();
		else if (mode == "easy")
			Grid::easyPlay();
		else return 0;
	}
	else {
		if (mode == "command")
			Grid::commandPlay(fileName);
		else if (mode == "easy")
			Grid::easyPlay(fileName);
		else return 0;
	}
}
