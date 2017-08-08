#include "vampire.h"
#include "player.h"

//ctor
Vampire::Vampire(){
   this->ch = 'V';
   this->HP = 50;
   this->Atk = 25;
   this->Def = 25;
}

//type pass
void Vampire::attack(Player &pl) {
   pl.useOn(*this);
}

//dtor
Vampire::~Vampire(){}
