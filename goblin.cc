#include "goblin.h"
#include "player.h"

//ctor
Goblin::Goblin() : Goldsteal(0) {
   this->ch = 'N';
   this->HP = 70;
   this->Atk = 5;
   this->Def = 10;
}

//type pass
void Goblin::attack(Player &pl) {
   pl.useOn(*this);
}

//addGoldsteal
void Goblin::addGoldsteal(int n){
   this->Goldsteal = Goldsteal + n;
}

//return Goldsteal
double Goblin::getGoldsteal() {
	return this->Goldsteal;
}

//dtor
Goblin:: ~Goblin() {}
