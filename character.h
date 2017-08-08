#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <string>
#include "cell.h"

class Character: public Cell {
  	protected:
   	int HP; // heals point
   	int Atk; //attack
   	int Def;	//defence
  	public:
   	Character();
   	int getHP();
   	int getAtk();
   	int getDef();
   	void setHP(int);
   	bool isdead();
   	virtual ~Character() = 0; 
};

#endif
