#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "enemy.h"

class Player;

class Goblin: public Enemy {
	double Goldsteal; //store the stealed gold
   public:
      Goblin();
      ~Goblin();
      void addGoldsteal(int);
		double getGoldsteal();
		void attack(Player &pl);
};
#endif
