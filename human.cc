#include "human.h"
#include "enemy.h"

Human::Human() {
   this->role = 'h';
   this->HP = 140;
   this->Atk = 20;
   this->Def = 20;
   this->maxHP = 140;
   this->defAtk = 20;
   this->defDef = 20;
}

Human::~Human(){}
