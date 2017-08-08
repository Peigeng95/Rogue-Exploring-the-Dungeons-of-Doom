#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "enemy.h"

class Player;

class Vampire: public Enemy {
   public:
      Vampire();
      ~Vampire();
		void attack(Player &pl);//virture method
};
#endif
