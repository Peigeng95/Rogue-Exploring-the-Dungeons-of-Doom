#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include "enemy.h"

class Player;

class Merchant: public Enemy {
   public:
      Merchant();
      ~Merchant();
      void attack(Player &); //set to hositle
};

#endif
