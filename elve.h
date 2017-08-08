#ifndef __ELVE_H__
#define __ELVE_H__
#include "player.h"

class Enemy;

class Elve: public Player {
   public:
      Elve();
      ~Elve();
		void addHp(int value); // always add
   	void addAt(int value); // always add
   	void addDf(int value); // always add
};

#endif
