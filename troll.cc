#include "troll.h"
#include "enemy.h"
#include <cstdlib>

//ctor
Troll::Troll(){
   this->ch = 'T';
   this->HP = 120;
   this->Atk = 25;
   this->Def = 15;
}

//genrate heal every auto move
void Troll::autoMove(int & newh, int &neww){
	newh = h + rand() % 3 - 1;
   neww = w + rand() % 3 - 1;
	this->HP = this->HP + 10;
}

//dtor
Troll::~Troll(){}
