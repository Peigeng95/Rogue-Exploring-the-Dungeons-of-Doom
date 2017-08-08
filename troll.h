#ifndef __TROLL_H__
#define __TROLL_H__
#include "enemy.h"

class Troll: public Enemy {
   public:
      Troll();
      ~Troll();
		void autoMove(int &, int &); // heal genrate every auto move
};
#endif
