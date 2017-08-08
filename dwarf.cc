#include "dwarf.h"
#include "enemy.h"

//ctor
Dwarf::Dwarf() {
   this->role = 'd';
   this->HP = 100;
   this->Atk = 20;
   this->Def = 30;
   this->maxHP = 100;
   this->defAtk = 20;
   this->defDef = 30;
}

//virtual method
void Dwarf:: addGold(int n){
	this->gold = this->gold + n + n; //double gold
}

//dtor
Dwarf::~Dwarf(){}
