#include "elve.h"
#include "enemy.h"

Elve::Elve() {
   this->role = 'e';
   this->HP = 140;
   this->Atk = 30;
   this->Def = 10;
   this->maxHP = 140;
   this->defAtk = 30;
   this->defDef = 10;
}

void Elve::addHp(int value){
	if(value < 0){ //if it is negative effect
		value = -value;
	}
	HP += value;
   if (HP > this->maxHP){
      HP = maxHP;
	}
}

void Elve::addAt(int value){
	if(value < 0){ //if it is negative effect
		value = -value;
	}
	Atk += value;
}

void Elve::addDf(int value){
	if(value < 0){ //if it is negative effect
		value = -value;
	}
	Def += value;
}

Elve::~Elve(){}
