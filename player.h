#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "character.h"
#include "enemy.h"
#include <string>

class Enemy;
class Goblin;
class Vampire;

class Player: public Character {
   protected:
   	char role;
   	double gold;
  		int maxHP;
   	int defAtk;
   	int defDef;
  	 	bool neutral;
   public:
   	Player();
   	double getGold();
   	char getRole();
   	bool ifNeu();
   	void setNeu();
		bool GameOver();
      void attack(Enemy &);
   	void useOn(Enemy &);
   	void useOn(Goblin &);
   	void useOn(Vampire &);
   	void reset();
   	virtual void addGold(double);
   	virtual void addHP(int value);
   	virtual void addAtk(int value);
   	virtual void addDef(int value);
   	virtual ~Player() = 0;
};

#endif
