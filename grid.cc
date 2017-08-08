#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <ncurses.h>
#include <vector>

#include "grid.h"
#include "printfile.h"

using namespace std;

//ctor
Grid::Grid(): theGrid(NULL), td(NULL), thePC(NULL), level(0), dra(0), file("default"){}

//dtor        
Grid::~Grid() {
	delete td;
   for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
         delete theGrid[i][j];
      }
      delete [] theGrid[i];
   }
   delete [] theGrid;
}

//NULL
Grid *Grid::game = 0;

//restart
void Grid::restart() {
	level = 0;
	this->clearStuff();
	delete thePC;
}

//reset grid
Grid *Grid::getInstance() {
	if (!game) {
		game = new Grid;
		atexit(cleanUp);
	}
	return game;
}

//delete pointer
void Grid::cleanUp() {
	delete game;
}

//Check lose
bool Grid::isItOver() {
	return this->thePC->	GameOver();
}

//check win
bool Grid::isItWin() {
	if (level < 6){
		return false;
	}
	else{
		return true;
	}
}

//set file name
void Grid::setFile(string fname) {
	this->file = fname;
}

//command play
void Grid::commandPlay(string fname) {
	Grid *game = Grid::getInstance();
	Print::printfile("choosechara.txt");
	if (fname == "dungeon.txt"){
 		game->newFloor();
	}
	else{
		game->newArrange(fname);
	}
 	char command;
 	cin >> command;
 	if (command == 'q'){
		return;
	}
 	else if ((command != 'h') && (command != 'e') && (command != 'o') && (command != 'd')){
     	game->addPlayer();
   }
 	else{
		game->addPlayer(command);
	}
	if (fname == "dungeon.txt") {
 		game->start();
	}
	else {
		game->startArg();
		game->setFile(fname);
	}
 	cout << *game << endl;
 	string cmd;
 	while (cin >> cmd) {
		if (cmd == "r") {
			game->restart();
	   	Print::printfile("choosechara.txt");
			if (fname == "dungeon.txt"){
 				game->newFloor();
			}
			else{
				game->newArrange(fname);
			}
 			cin >> command;
			if (command == 'q'){
				return;
			}
 			else if ((command != 'h') && (command != 'e') && (command != 'o') && (command != 'd')){
     			game->addPlayer();
     		}
 			else{
				game->addPlayer(command);
			}	
			if (fname == "dungeon.txt") {
		 		game->start();
			}
			else {
				game->startArg();
				game->setFile(fname);
			}
 			cout << *game << endl;
			continue;
		}
   	else if (cmd == "Heal") {// add HP to test
      	game->thePC->setHP(-1000);
   	}
		else if (cmd.at(0) == 'a'){ // attack
			if ((cmd.substr(1,2) == "no") || (cmd.substr(1,2) == "so") || (cmd.substr(1,2) == "we") || (cmd.substr(1,2) == "ea") ||
				 (cmd.substr(1,2) == "ne") || (cmd.substr(1,2) == "nw") || (cmd.substr(1,2) == "se") || (cmd.substr(1,2) == "sw")){
	      	game->pcAttack(cmd.substr(1,2));
				game->emAction();
			}
			else {
				cout << "error: invaild command!" << endl;
				continue;
			}
   	}
   	else if (cmd.at(0) == 'u') { //use 
			if ((cmd.substr(1,2) == "no") || (cmd.substr(1,2) == "so") || (cmd.substr(1,2) == "we") || (cmd.substr(1,2) == "ea") ||
				 (cmd.substr(1,2) == "ne") || (cmd.substr(1,2) == "nw") || (cmd.substr(1,2) == "se") || (cmd.substr(1,2) == "sw")){
	      	game->eatPotion(cmd.substr(1,2));
				game->emAction();
			}
			else {
				cout << "error: invaild command!" << endl;
				continue;
			}
   	}
		else if (cmd.at(0) == 'q'){
			break;
		}
   	else if ((cmd == "no") || (cmd == "so") || (cmd == "we") || (cmd == "ea") ||
					(cmd == "ne") || (cmd == "nw") || (cmd == "se") || (cmd == "sw")){
				game->pcMove(cmd);
				if (game->isItWin()) {
				Print::printfrom("win.txt", 29);
				cout << "Your score:  " << game->getScore() << endl;
				break;
				}
		}
		else {
			cout << "error: invaild command!" << endl;
			continue;
		}
		if (game->isItOver()) {
			Print::printfrom("lose.txt", 30);
			break;
		}
   	cout << *game << endl;
    }
}


void Grid::easyPlay(string fname) {
	const char NO = 'w';
	const char SO = 's';
	const char WE = 'a';
	const char EA = 'd';
	const char NW = '1';
	const char NE = '3';
	const char SW = 'z';
	const char SE = 'c';
	initscr();
   clear();
   noecho();
   cbreak();
	curs_set(0);
   start_color();
   init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);	
	init_pair(3, COLOR_RED, COLOR_BLACK);
	Print::printfile_easy("choosecharaforeasy.txt");
	Grid *game = Grid::getInstance();
	if (fname == "dungeon.txt"){
 		game->newFloor();
	}
	else{
		game->newArrange(fname);
	}
	char command;
	cin >> command;
 	if (command == 'q'){//quit game
		clear();
		endwin();
		exit(0);
	}
 	else if ((command != 'h') && (command != 'e') && (command != 'o') && (command != 'd')) {
     	game->addPlayer();
   }
 	else{
		game->addPlayer(command);
	}
	clear();
	if (fname == "dungeon.txt") {
 		game->start();
	}
	else {
		game->startArg();
		game->setFile(fname);
	}
	cout << game << endl;
	char cmd;
	while (cin >> cmd) {
	switch (cmd) {
		case 'r'://restart game
			game->restart();
	   	Print::printfile_easy("choosecharaforeasy.txt");
			if (fname == "dungeon.txt"){
 				game->newFloor();
			}
			else{
				game->newArrange(fname);
			}
 			cin >> command;
 			if (command == 'q') {//quit game
				clear();
				endwin();
				exit(0);
			}
 			else if ((command != 'h') && (command != 'e') && (command != 'o') && (command != 'd')){
     			game->addPlayer();
   		}
 			else {
				game->addPlayer(command);
			}
 			clear();
 			if (fname == "dungeon.txt") {
 				game->start();
			}
			else {
				game->startArg();
				game->setFile(fname);
			}
 			cout << game << endl;
			continue; 
			break;
		case 'H': //and HP to test
		   game->thePC->setHP(-1000);break;
		case 'q': //quit
			clear();
			endwin();
			exit(0); 
			break;
   	case NO:case SO:case WE:case EA:
		case NW:case NE:case SW:case SE://move case
			switch(cmd) {
				case NW:
					game->pcMove("nw");
					break;
				case NE:
					game->pcMove("ne");
					break;
				case SW:
					game->pcMove("sw");
					break;
				case SE:
					game->pcMove("se");
					break;
				case NO:
					game->pcMove("no");
					break;
				case SO:
					game->pcMove("so");
					break;
				case WE:
					game->pcMove("we");
					break;
				case EA:
					game->pcMove("ea");
					break;
			}
			if (game->isItWin()) {//check if PC win 
				string win;
				stringstream score;
				Print::printfile_easy("win.txt");
				score << "Your Score: " << game->getScore(); //print score
				getline(score, win);
				mvaddstr(24, 6, win.c_str());
				refresh();
				cin >> cmd;
				clear();
				endwin();
				exit(0);
			} 
			break;
		case 'j': // attack case
			cin >> cmd;
			switch (cmd) {
				case NW:
					game->pcAttack("nw");
					break;
				case NE:
					game->pcAttack("ne");
					break;
				case SW:
					game->pcAttack("sw");
					break;
				case SE:
					game->pcAttack("se");
					break;
				case NO:
					game->pcAttack("no");
					break;
				case SO:
					game->pcAttack("so");
					break;
				case WE:
					game->pcAttack("we");
					break;
				case EA:
					game->pcAttack("ea");
					break;
			} 
			game->emAction();
			break;
		case 'k': //use poition case
			cin >> cmd;
			switch (cmd) {
				case NW:
					game->eatPotion("nw");
					break;
				case NE:
					game->eatPotion("ne");
					break;
				case SW:
					game->eatPotion("sw");
					break;
				case SE:
					game->eatPotion("se");
					break;
   			case NO:
					game->eatPotion("no");
					break;
				case SO:
					game->eatPotion("so");
					break;
				case WE:
					game->eatPotion("we");
					break;
				case EA:
					game->eatPotion("ea");
					break;
			}
			game->emAction();
			break;
		default:
			continue;
		}
		if (game->isItOver()) {// check if PC is dead
			Print::printfile_easy("lose.txt");
			refresh();
			cin >> cmd;
			break;
		}
   cout << game;
    }
 endwin(); 
}


int Grid::getScore() {
	if (thePC->getRole() == 'h')
		return (int)(this->thePC->getGold() * 2);
	else
		return this->thePC->getGold();
}


int Grid::getLevel() {
   return level;
}

void Grid::clearStuff() {
   delete td;
   theGrid[thePC->getH()][thePC->getW()] = NULL;
   for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
         if (theGrid[i][j] != NULL)
         delete theGrid[i][j];
      }
      delete [] theGrid[i];
   }
   delete [] theGrid;
}


void Grid::newFloor(string fname) {
	for (int nr = 0; nr < 5; nr++){
		theCha[nr].cleanRoom();
	}
	if (++level != 1){
		this->clearStuff();
	}
	dra = 0;
   td = new Board();
   fstream f(fname.c_str());
   string s;
	int det_H = height * (level - 1);
	if (level >= 6) det_H = 0;
   for(;;){
      theGrid = new Cell**[height];
      for(int i = 0; i < det_H+height; i++) {
         getline(f,s);
         if(f.eof()){
				break;
			}	
			if (i >= det_H) {
	         theGrid[i-det_H] = new Cell*[width];
   	      for(int j = 0; j < width; j++) {
   	         theGrid[i-det_H][j] = new Cell(s.at(j), td);
   	         theGrid[i-det_H][j]->setCoords(i-det_H, j);
   	      }
			}
      }
      break;
   }
	for (int x = 0; x < height; x++) { //scan the room
		for (int y = 0; y < width; y++) {
			if (theGrid[x][y]->getSymbol() == '.') {
				if ((x - 1 >= 0) && (theGrid[x-1][y]->getSymbol() == '.'))
					theGrid[x][y]->addNeighbour(theGrid[x-1][y]);
				if ((y - 1 >= 0) && (theGrid[x][y-1]->getSymbol() == '.'))
					theGrid[x][y]->addNeighbour(theGrid[x][y-1]);
				if ((x + 1 >= 0) && (theGrid[x+1][y]->getSymbol() == '.'))
					theGrid[x][y]->addNeighbour(theGrid[x+1][y]);
				if ((y + 1 >= 0) && (theGrid[x][y+1]->getSymbol() == '.'))
					theGrid[x][y]->addNeighbour(theGrid[x][y+1]);
			}
		}
	}
	int numRoom = 0;
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			if ((theGrid[x][y]->getSymbol() == '.') and
				 (theGrid[x][y]->Set()==false)) {
				theGrid[x][y]->arrangeRoom(theCha[numRoom]);
				numRoom++;
			}
		}
	}
}

	
void Grid::newArrange(string fname) {
	if (++level != 1){
		this->clearStuff();
	}
	dra = 0;
   td = new Board();
	vector<Item *> dragonH;
	vector<Dragon *> dragon;
   fstream f(fname.c_str());
   string s;
	int potNum = 0;
	int treaNum = 0;
	int eneNum = 0;
	int det_H = height * (level - 1);
	if (level >= 6) det_H = 0;
   for(;;){
      theGrid = new Cell**[height];
      for(int i = 0; i < det_H+height; i++){
         getline(f,s);
         if(f.eof()) break;			
			if (i >= det_H) {
	         theGrid[i-det_H] = new Cell*[width];
   	      for(int j = 0; j < width; j++) {
					switch (s.at(j)) {      //check what is it ?
						case '0':	theGrid[i-det_H][j] = new Item("RH");
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setPrev('.'); 
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										myPo[potNum] = static_cast<Item*>(theGrid[i-det_H][j]); 
										potNum++;
										break;
						case '1':	theGrid[i-det_H][j] = new Item("BA");
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setPrev('.'); 
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										myPo[potNum] = static_cast<Item*>(theGrid[i-det_H][j]); ; 
										potNum++;
										break;
						case '2':	theGrid[i-det_H][j] = new Item("BD");
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setPrev('.'); 
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										myPo[potNum] = static_cast<Item*>(theGrid[i-det_H][j]); ; 
										potNum++;
										break;
						case '3':	theGrid[i-det_H][j] = new Item("PH");
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setPrev('.'); 
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										myPo[potNum] = static_cast<Item*>(theGrid[i-det_H][j]); ; 
										potNum++;
										break;
						case '4':	theGrid[i-det_H][j] = new Item("WA");
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setPrev('.'); 
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										myPo[potNum] = static_cast<Item*>(theGrid[i-det_H][j]); ; 
										potNum++;
										break;
						case '5':	theGrid[i-det_H][j] = new Item("WD");
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setPrev('.'); 
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										myPo[potNum] = static_cast<Item*>(theGrid[i-det_H][j]); ; 
										potNum++;
										break;
						case '6':	theGrid[i-det_H][j] = new Item("normal gold pile");
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setPrev('.'); 
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										myTr[treaNum] = static_cast<Item*>(theGrid[i-det_H][j]); 
										treaNum++;
										break;
						case '7':	theGrid[i-det_H][j] = new Item("small horde");
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setPrev('.'); 
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										myTr[treaNum] = static_cast<Item*>(theGrid[i-det_H][j]); 
										treaNum++;
										break;
						case '8':	theGrid[i-det_H][j] = new Item("merchant horde");
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										theGrid[i-det_H][j]->setPrev('.'); 
										myTr[treaNum] = static_cast<Item*>(theGrid[i-det_H][j]); 
										treaNum++;
										break;
						case '9':	theGrid[i-det_H][j] = new Item("dragon horde");
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										theGrid[i-det_H][j]->setPrev('.'); 
										myTr[treaNum] = static_cast<Item*>(theGrid[i-det_H][j]); 
										treaNum++;
										dragonH.push_back(static_cast<Item *>(theGrid[i-det_H][j])); 
										break;
						case 'V':	theGrid[i-det_H][j] = new Vampire();
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										theGrid[i-det_H][j]->setPrev('.'); 
										myEn[eneNum] = static_cast<Enemy*>(theGrid[i-det_H][j]); 
										eneNum++;	break;
						case 'W':	theGrid[i-det_H][j] = new Werewolf();
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										theGrid[i-det_H][j]->setPrev('.'); 
										myEn[eneNum] = static_cast<Enemy*>(theGrid[i-det_H][j]); 
										eneNum++;	break;
						case 'T':	theGrid[i-det_H][j] = new Troll();
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										theGrid[i-det_H][j]->setPrev('.'); 
										myEn[eneNum] = static_cast<Enemy*>(theGrid[i-det_H][j]); 
										eneNum++;	break;
						case 'N':	theGrid[i-det_H][j] = new Goblin();
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										theGrid[i-det_H][j]->setPrev('.'); 
										myEn[eneNum] = static_cast<Enemy*>(theGrid[i-det_H][j]); 
										eneNum++;	break;
						case 'X':	theGrid[i-det_H][j] = new Phoenix();
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										theGrid[i-det_H][j]->setPrev('.'); 
										myEn[eneNum] = static_cast<Enemy*>(theGrid[i-det_H][j]); 
										eneNum++;	break;
						case 'M':	theGrid[i-det_H][j] = new Merchant();
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										theGrid[i-det_H][j]->setPrev('.'); 
										myEn[eneNum] = static_cast<Enemy*>(theGrid[i-det_H][j]); 
										eneNum++;	break;
						case 'D':	theGrid[i-det_H][j] = new Dragon();
										theGrid[i-det_H][j]->setDisplay(td);
										theGrid[i-det_H][j]->setCoords(i-det_H, j);
										theGrid[i-det_H][j]->setPrev('.'); 
										myEn[eneNum] = static_cast<Enemy*>(theGrid[i-det_H][j]); 
										dra++; 
										eneNum++;
										dragon.push_back(static_cast<Dragon *>(theGrid[i-det_H][j])); 
										break;
						default:	theGrid[i-det_H][j] = new Cell(s.at(j), td);
   	         				theGrid[i-det_H][j]->setCoords(i-det_H, j);
					}
   	      }
			}
      }
		for (unsigned int x = 0; x < dragonH.size(); x++) {
			for (unsigned int y = 0; y < dragon.size(); y++) {
				if (dragon[y]->hashorde()) continue;
				for (int dr = -1; dr <= 1; dr++) {
      			for (int dc = -1; dc <= 1; dc++) {
         			if (dr == 0 && dc == 0) continue;
         			if ((dragonH[x]->getH()+dr == dragon[y]->getH()) and
							 (dragonH[x]->getW()+dc == dragon[y]->getW())) {
								dragon[y]->setH(dragonH[x]);
								break;
						}
					}
				}
			}
		}
      break;
   }
}


//ifRange: if in enemy range
bool Grid::ifRange(int &h, int &w) {
   for (int i = h - 1; i <= h + 1; i++) {
      for (int j = w - 1; j <= w + 1; j++) {
         if (theGrid[i][j]->getSymbol() == '@') {
            h = i;
            w = j;
            return true;
         }
      }
   }
   return false;
}



//enemy Action
void Grid::emAction() {
   int newr, newc;
   int r, c;
   int oldHp, newHp;
   int aim_r, aim_c; // attacking aiming coords
   for (int i = 0; i < 20; i++) {
    if (myEn[i] == NULL) continue;
    else if (myEn[i]->isdead()) { delete myEn[i]; myEn[i] = NULL; continue; }
      aim_r = myEn[i]->getH();
      aim_c = myEn[i]->getW();
      if(this->ifRange(aim_r, aim_c)) {
         if (((!myEn[i]->ifHost()) && (!thePC->ifNeu())) ||
              (myEn[i]->ifHost())) {
					int x = rand() % 2;
					if(x == 0){
              		oldHp = thePC->getHP();
              		thePC->attack(*myEn[i]);
              		newHp = thePC->getHP();
              		stringstream sout;
              		string temp;   //add description
              		sout << myEn[i]->getSymbol() << " deals ";
              		sout << oldHp - newHp << " damage to PC. ";
              		getline(sout, temp);
              		desc = desc + temp;
					}
					else{
						stringstream sout;
              		string temp;   //add description
              		sout << myEn[i]->getSymbol() << " Miss ";
              		getline(sout, temp);
              		desc = desc + temp;
					}
         }
      }
      else {
         r = myEn[i]->getH();
         c = myEn[i]->getW();
         newr = r;
         newc = c;
         myEn[i]->autoMove(newr, newc);
         if (theGrid[newr][newc]->getSymbol() == '.') {
            delete theGrid[newr][newc];
            theGrid[r][c] = new Cell('.', td);
            theGrid[r][c]->setCoords(r, c);
            theGrid[newr][newc] = myEn[i];
            myEn[i]->setCoords(newr, newc);
         }
     }
   }
}

//check if PC is near a potion
bool Grid::nearPotion() {
   for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
         if (i == 0 && j == 0) continue;
         if (theGrid[thePC->getH()+i][thePC->getW()+j]->getSymbol() == 'P') {
            desc = desc + " and sees an unknown potion. ";
            return true;
          }
      }
   }
   desc = desc + ". ";
   return false;
}

//PC use a Potion
void Grid::eatPotion(string m) {
   int newr, newc;
   int r = thePC->getH();
   int c = thePC->getW();
   if(m == "no") {
      newr = r - 1;
      newc = c;
   }
   if(m == "so") {
      newr = r + 1;
      newc = c;
   }
   if(m == "ea") {
      newr = r;
      newc = c + 1;
   }
   if(m == "we") {
      newr = r;
      newc = c - 1;
   }
   if(m == "ne") {
      newr = r - 1;
      newc = c + 1;
   }
   if(m == "nw") {
      newr = r - 1;
      newc = c - 1;
   }
   if(m == "se") {
      newr = r + 1;
      newc = c + 1;
   }
   if(m == "sw") {
      newr = r + 1;
      newc = c - 1;
   }
   if (theGrid[newr][newc]->getSymbol() == 'P') {
         Item *temp = static_cast<Item*>(theGrid[newr][newc]);
         temp->useOn(*thePC);
            theGrid[newr][newc] = new Cell('.', td);
            theGrid[newr][newc]->setCoords(newr,newc);
         desc = "PC uses " + temp->getName() + ". ";
         delete temp;
   }
   else { desc = "There is no potion there ! "; }
       
}


//pcAttack
void Grid::pcAttack(string m) {
   int newr, newc, oldHp, newHp;
   stringstream sout;
   int r = thePC->getH();
   int c = thePC->getW();
   if(m == "no") {
      newr = r - 1;
      newc = c;
   }
   if(m == "so") {
      newr = r + 1;
      newc = c;
   }
   if(m == "ea") {
      newr = r;
      newc = c + 1;
   }
   if(m == "we") {
      newr = r;
      newc = c - 1;
   }
   if(m == "ne") {
      newr = r - 1;
      newc = c + 1;
   }
   if(m == "nw") {
      newr = r - 1;
      newc = c - 1;
   }
   if(m == "se") {
      newr = r + 1;
      newc = c + 1;
   }
   if(m == "sw") {
      newr = r + 1;
      newc = c - 1;
   }
   if	(dynamic_cast<Enemy *>(theGrid[newr][newc]) != NULL) {
         Enemy *theEn = static_cast<Enemy*>(theGrid[newr][newc]);
         oldHp = theEn->getHP();
         theEn->attack(*thePC);
         newHp = theEn->getHP();
         if(theEn->isdead()) { //check if the enemy is dead
            newHp = theEn->getHP(); // reassign
            if(theEn->getSymbol() == 'N') {
					//int x = theEn -> getGoldsteal + 1;
               thePC->addGold(5);
	       		theGrid[newr][newc] = new Cell('.', td);
               theGrid[newr][newc]->setCoords(newr,newc);
            }
            else if (theEn->getSymbol() == 'D') {
               static_cast<Dragon*>(theEn)->setTaken();
	       		theGrid[newr][newc] = new Cell('.', td);
               theGrid[newr][newc]->setCoords(newr,newc);
            }
	    		else if (theEn->getSymbol() == 'M') {
	       		theGrid[newr][newc] = new Item("merchant horde");
	       		theGrid[newr][newc]->setDisplay(td);
	       		theGrid[newr][newc]->setCoords(newr, newc);
	    		}
	    		else {
	       		thePC->addGold(1);
	       		theGrid[newr][newc] = new Cell('.', td);
               theGrid[newr][newc]->setCoords(newr,newc);
	    		}
         }
         sout << "PC deals ";
         sout << oldHp - newHp << " damage ";
         sout << "to " << theEn->getSymbol() << " (";
         sout << newHp << " HP). ";
         getline(sout, desc);
   }
   else { desc = "Easy boy ! There is no enemy in that place."; }
       
}
 
//pcMove
void Grid::pcMove(string m) {
   int newr, newc;
   int r = thePC->getH();
   int c = thePC->getW();
   desc = "PC moves ";
   if(m == "no") {
      newr = r - 1;
      newc = c;
      desc = desc + "North"; // consider see a potion
   }
   else if(m == "so") {
      newr = r + 1;
      newc = c;
      desc = desc + "South";
   }
   else if(m == "ea") {
      newr = r;
      newc = c + 1;
      desc = desc + "East";
   }
   else if(m == "we") {
      newr = r;
      newc = c - 1;
      desc = desc + "West";
   }
   else if(m == "ne") {
      newr = r - 1;
      newc = c + 1;
      desc = desc + "North-East";
   }
   else if(m == "nw") {
      newr = r - 1;
      newc = c - 1;
      desc = desc + "North-West";
   }
   else if(m == "se") {
      newr = r + 1;  
      newc = c + 1;
      desc = desc + "South-East";
   }
   else if(m == "sw") {
      newr = r + 1;
      newc = c - 1;
      desc = desc + "South-West";
   }
   if((theGrid[newr][newc]->getSymbol() == '.') or
       (theGrid[newr][newc]->getSymbol() == '+') or
       (theGrid[newr][newc]->getSymbol() == '#')) {
       char temp = theGrid[newr][newc]->getSymbol();
       delete theGrid[newr][newc];
       theGrid[r][c] = new Cell(thePC->getPrev(), td);
       theGrid[r][c]->setCoords(r, c);
       theGrid[newr][newc] = thePC;
       thePC->setCoords(newr,newc);
       thePC->setPrev(temp);
   	 nearPotion();
		 game->emAction();
   }
   else if ((theGrid[newr][newc]->getSymbol() == 'G') and
            (static_cast<Item*>(theGrid[newr][newc])->getTaken())) {
      Item *temp = static_cast<Item*>(theGrid[newr][newc]);
      temp->useOn(*thePC);
      desc = desc + " and pick up a " + temp->getName();
      delete theGrid[newr][newc];
      theGrid[r][c] = new Cell(thePC->getPrev(), td);
      theGrid[r][c]->setCoords(r, c);
      theGrid[newr][newc] = thePC;
      thePC->setCoords(newr,newc);
      thePC->setPrev('.');
   	nearPotion();
		game->emAction();
   }
   else if ((theGrid[newr][newc]->getSymbol() == 'G') and
            !(static_cast<Item*>(theGrid[newr][newc])->getTaken())) {
      desc = "Go kill the Dargon first !";
   }
   else if (theGrid[newr][newc]->getSymbol() == '\\') {
      thePC->reset();
		for (int i = 0; i < 20; i++) {
    		if (myEn[i] == NULL) continue;
    		else if (myEn[i]->isdead()) {
				delete myEn[i]; myEn[i] = NULL; continue;
			}
		}
		if (this->file == "default") {
      	this->newFloor();
      	this->start();
		}
		else {
			this->newArrange(file);
			this->startArg();
		}
   }
   else {
      desc = "Oh oh ! you can't go there!";
      return;
   }
}



void Grid::addPlayer(char pl) {
   switch (pl) {
      case 'h': thePC = new Human();break;
      case 'd': thePC = new Dwarf();break;
      case 'o': thePC = new Orc();break;
      case 'e': thePC = new Elve();break;
   }
}

void Grid::genePotion() {
   int r = 0;
	int c = 0;
	int room, pos;  
   int typ;
   for(int i = 0; i < 10; i++) {
      myPo[i] = NULL;
   }
   for(int i = 0; i < 10; i++) {
		for(;;){
      	room = rand() % 5;
			if (theCha[room].isFilled()) continue;
			else {
				pos = theCha[room].giveCoords(r, c);
				break;
			}
      }
      typ = rand() % 6;
      if (typ == 0) {
         myPo[i] = new Item("RH");
         myPo[i]->setDisplay(td);
         myPo[i]->setPrev('.');
         myPo[i]->setCoords(r, c);
			theCha[room].changePos(pos, myPo[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myPo[i];   
      }
      if (typ == 1) {
         myPo[i] = new Item("PH");
         myPo[i]->setDisplay(td);
         myPo[i]->setPrev('.');
         myPo[i]->setCoords(r, c);
			theCha[room].changePos(pos, myPo[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myPo[i];   
      }
      if (typ == 2) {
         myPo[i] = new Item("BA");
         myPo[i]->setDisplay(td);
         myPo[i]->setPrev('.');
         myPo[i]->setCoords(r, c);
			theCha[room].changePos(pos, myPo[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myPo[i];   
      }
      if (typ == 3) {
         myPo[i] = new Item("WA");
         myPo[i]->setDisplay(td);
         myPo[i]->setPrev('.');
         myPo[i]->setCoords(r, c);
			theCha[room].changePos(pos, myPo[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myPo[i];   
      }
      if (typ == 4) {
         myPo[i] = new Item("BD");
         myPo[i]->setDisplay(td);
         myPo[i]->setPrev('.');
         myPo[i]->setCoords(r, c);
			theCha[room].changePos(pos, myPo[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myPo[i];   
      }
      if (typ == 5) {
         myPo[i] = new Item("WD");
         myPo[i]->setDisplay(td);
         myPo[i]->setPrev('.');
         myPo[i]->setCoords(r, c);
			theCha[room].changePos(pos, myPo[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myPo[i];   
      }
   }
}


void Grid::geneTrea() {
   int r = 0;
	int c = 0;
	int room, pos;   // random
   int typ;
   for(int i = 0; i < 10; i++) {
      myTr[i] = NULL;
   }
   //create treasures
   for(int i = 0; i < 10; i++) {
		while (true) {
      	room = rand() % 5;
			if (theCha[room].isFilled()) continue;
			else {
				pos = theCha[room].giveCoords(r, c);
				break;
			}
      }
      typ = rand() % 10;
      if (typ <= 5) {
         myTr[i] = new Item("normal gold pile");
         myTr[i]->setDisplay(td);
         myTr[i]->setPrev('.');
         myTr[i]->setCoords(r, c);
			theCha[room].changePos(pos, myTr[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myTr[i];   
      }
      if ((typ <= 8) and (typ > 5)) {
         myTr[i] = new Item("small horde");
         myTr[i]->setDisplay(td);
         myTr[i]->setPrev('.');
         myTr[i]->setCoords(r, c);
			theCha[room].changePos(pos, myTr[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myTr[i];   
      }
      if (typ == 9) {
         myTr[i] = new Item("dragon horde");
         myTr[i]->setDisplay(td);
         myTr[i]->setPrev('.');
         myTr[i]->setCoords(r, c);
			theCha[room].changePos(pos, myTr[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myTr[i]; 
         myEn[dra] = new Dragon;
         myEn[dra]->setDisplay(td);
         static_cast<Dragon*>(myEn[dra])->setH(myTr[i]);
         myEn[dra]->setPrev('.');
         int d_r, d_c;
         while (true) {
            d_r = rand() % 3 - 1 + r;
            d_c = rand() % 3 - 1 + c;   
            if (theGrid[d_r][d_c]->getSymbol() == '.') break;
         }
         myEn[dra]->setCoords(d_r, d_c);
         delete theGrid[d_r][d_c];
         theGrid[d_r][d_c] = myEn[dra];
         dra++;
      }
   }
}


void Grid::geneEnemy() {
   int r = 0;
	int c = 0;
	int room, pos;   // random
   int typ;
   for(int i = dra; i < 20; i++) {
      myEn[i] = NULL;
   }
   for(int i = dra; i < 20; i++) {
		while (true) {
      	room = rand() % 5;
			if (theCha[room].isFilled()) continue;
			else {
				pos = theCha[room].giveCoords(r, c);
				break;
			}
      }
      typ = rand() % 18;
      if((typ >= 0) && (typ <= 3)) {
         myEn[i] = new Werewolf;
         myEn[i]->setDisplay(td);
         myEn[i]->setPrev('.');
         myEn[i]->setCoords(r, c);
			theCha[room].changePos(pos, myEn[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myEn[i];   
      }
      if((typ >= 4) && (typ <= 6)) {
         myEn[i] = new Vampire;
         myEn[i]->setDisplay(td);
         myEn[i]->setPrev('.');
         myEn[i]->setCoords(r, c);
			theCha[room].changePos(pos, myEn[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myEn[i];   
      }
      if((typ >= 7) && (typ <= 11)) {
         myEn[i] = new Goblin;
         myEn[i]->setDisplay(td);
         myEn[i]->setPrev('.');
         myEn[i]->setCoords(r, c);
			theCha[room].changePos(pos, myEn[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myEn[i];   
      }
      if((typ == 12) || (typ == 13)) {
         myEn[i] = new Troll;
         myEn[i]->setDisplay(td);
         myEn[i]->setPrev('.');
         myEn[i]->setCoords(r, c);
			theCha[room].changePos(pos, myEn[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myEn[i];   
      }
      if((typ == 14) || (typ == 15)) {
         myEn[i] = new Phoenix;
         myEn[i]->setDisplay(td);
         myEn[i]->setPrev('.');
         myEn[i]->setCoords(r, c);
			theCha[room].changePos(pos, myEn[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myEn[i];   
      }
      if((typ == 16) || (typ == 17)) {
         myEn[i] = new Merchant;
         myEn[i]->setDisplay(td);
         myEn[i]->setPrev('.');
         myEn[i]->setCoords(r, c);
			theCha[room].changePos(pos, myEn[i]);
         delete theGrid[r][c];
         theGrid[r][c] = myEn[i];   
      }
   }
}



void Grid::start() {
   int r = 0; 
	int c = 0;
	int room, pos;
   desc = "Player character has spawned.";
   for(;;){
      	room = rand() % 5;
			if (theCha[room].isFilled()) continue;
			else {
				pos = theCha[room].giveCoords(r, c);
				break;
			}
   } 
   thePC->setDisplay(td);
   thePC->setCoords(r, c);
	theCha[room].changePos(pos, thePC);
   delete theGrid[r][c];
   theGrid[r][c] = thePC;
   thePC->setPrev('.');
   for(;;){
      	room = rand() % 5;
			if (theCha[room].isFilled()) continue;
			else {
				pos = theCha[room].giveCoords(r, c);
				break;
			}
   }
   delete theGrid[r][c];
   theGrid[r][c] = new Cell('\\', td);
	theCha[room].changePos(pos, theGrid[r][c]);
   theGrid[r][c]->setCoords(r, c);
   this->genePotion();
   this->geneTrea();
   this->geneEnemy();
}


void Grid::startArg() {
	int r = 0; 
	int c = 0;
   desc = "Player character has spawned.";
   while (true) {
      r = rand() % height;
      c = rand() % width;
      if (theGrid[r][c]->getSymbol() == '.') break;
   }
   thePC->setDisplay(td);
   thePC->setCoords(r, c);
   delete theGrid[r][c];
   theGrid[r][c] = thePC;
   thePC->setPrev('.');
}


//           operator<< over load

ostream &operator<<(ostream &out, const Grid &g) {
   out << *(g.td) << endl;
   out << "Race: ";
   switch (g.thePC->getRole()) {
      case 'd': out << "Dwarf ";break;
      case 'o': out << "Orc ";break;
      case 'h': out << "Human ";break;
      case 'e': out << "Elve ";break;
   }
   out << "Gold: " << g.thePC->getGold(); 
   out << "                                              Floor " <<  g.level << endl;
   out << "HP: " << g.thePC->getHP() << endl;
   out << "Atk: " << g.thePC->getAtk() << endl;
   out << "Def: " << g.thePC->getDef() << endl;
   out << "Action: " << g.desc;
 return out;
}



ostream &operator<<(ostream &out, const Grid *g) {
   out << g->td;
	string first = "Race: ";
   switch (g->thePC->getRole()) {
      case 'd': first = first + "Dwarf ";break;
      case 'o': first = first + "Orc ";break;
      case 'h': first = first + "Human ";break;
      case 'e': first = first + "Elve ";break;
   }
	first = first + "Gold: ";
	ostringstream convG;
	convG << g->thePC->getGold();
	first = first + convG.str();
	ostringstream convF;
	convF << g->level;
   string floor = "Floor: " + convF.str();
	ostringstream convH;
	convH << "HP: " << g->thePC->getHP();
	string heal = convH.str();
	ostringstream convA;
	convA << "Atk: " << g->thePC->getAtk();
	string attack = convA.str();
	ostringstream convD;
	convD << "Def: " << g->thePC->getDef() << endl;
	string defen = convD.str();
	ostringstream convC;
	convC << "Action: " << g->desc;
	string action = convC.str();

	clrtoeol();
	mvaddstr(height, 0, first.c_str());
   mvaddstr(height, width-10, floor.c_str());
	clrtoeol();
	mvaddstr(height+1, 0, heal.c_str());
	clrtoeol();
	mvaddstr(height+2, 0, attack.c_str());
	clrtoeol();
	mvaddstr(height+3, 0, defen.c_str());
	clrtoeol();
	mvaddstr(height+4, 0, action.c_str());
	refresh();
	return out;
}
