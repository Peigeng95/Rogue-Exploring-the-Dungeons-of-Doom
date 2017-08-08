#ifndef __GRID_H__
#define __GRID_H__


#include <iostream>
#include <ncurses.h>
#include <string>
#include "cell.h"
#include "board.h"
#include "character.h"
#include "player.h"
#include "human.h"
#include "dwarf.h"
#include "elve.h"
#include "orc.h"
#include "enemy.h"
#include "vampire.h"
#include "werewolf.h"
#include "troll.h"
#include "goblin.h"
#include "merchant.h"
#include "dragon.h"
#include "phoenix.h"
#include "item.h"
#include "room.h"

class Grid {
	Cell ***theGrid;
	Board *td;
	Player *thePC;
	int level;
	int dra; // num of dragon
	Room theCha[5];
	std::string desc;
	std::string file;
	Enemy *myEn[20];
	Item *myPo[20];
	Item *myTr[10];
 	public:
   	Grid();
   	~Grid();
		bool isItOver();		//if PC dead
		bool isItWin();		//uf PC win
		int getLevel();			//return level
		void clearStuff();		
		static Grid *game;
		static Grid *getInstance();
		static void cleanUp();
		static void easyPlay(std::string fname = "dungeon.txt");		//easy play
		static void commandPlay(std::string fname = "dungeon.txt");	//command play
		void setFile(std::string);		//set arranged file name
		int getScore();				//return score PC get
		void start();			//start game
		void startArg();
		void emAction();           // emeny action: Auto move Auto attack  
		void pcMove(std::string m);	// PC move
		void eatPotion(std::string);       //use potion
		void pcAttack(std::string m);	   //PC attack
		void newFloor(std::string fname = "dungeon.txt");
		void newArrange(std::string fname);
		void restart();				//rset the game
		void addPlayer(char pl = 's');		// add a play to the game
		bool nearPotion();                //see if PC is near a potion
		void genePotion();				//gene all Potion
		void geneTrea();				//gene all GOld	
		void geneEnemy();					// gene all enemy
		bool ifRange(int &r, int &c);			// enemy auto attack
  	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
  	friend std::ostream &operator<<(std::ostream &out, const Grid *g);
};

#endif
