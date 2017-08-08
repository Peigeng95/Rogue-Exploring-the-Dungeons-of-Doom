#include "orc.h"
#include "enemy.h"

//ctor
Orc::Orc() {
   this->role = 'o';
   this->HP = 180;
   this->Atk = 30;
   this->Def = 25;
   this->maxHP = 180;
   this->defAtk = 30;
   this->defDef = 25;
}

//half gold
void Orc:: addGold(double n){
	double m = n * 0.5;
	this->gold = this->gold + m;
}

//dtor
Orc::~Orc(){}
