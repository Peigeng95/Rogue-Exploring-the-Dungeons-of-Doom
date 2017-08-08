#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "character.h"

class Player;

class Enemy: public Character {
  	protected:
   	bool hostile;
  	public:
   	Enemy();
   	bool ifHost();
   	virtual void autoMove(int &, int &);
   	virtual void attack(Player &);
   	void useOn(Player &);
   	virtual ~Enemy() = 0;
 };

#endif
