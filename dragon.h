#ifndef __DRAGON_H__
#define __DRAGON_H__
#include "enemy.h"

class Item;

class Dragon: public Enemy {
   Item *horde;
   public:
      Dragon();
		bool hashorde();
      void setH(Item *);
      void setTaken();
      void autoMove(int &, int &);
      ~Dragon();
};

#endif
