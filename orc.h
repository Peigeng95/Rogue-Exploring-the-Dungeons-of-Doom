#ifndef __ORC_H__
#define __ORC_H__
#include "player.h"

class Enemy;

class Orc: public Player {
   public:
		void addGold(double); // half gold
      Orc();
      ~Orc();
};

#endif
