#include "merchant.h"
#include "player.h"

//ctor
Merchant::Merchant() {
   this->ch = 'M';
   this->hostile = false;
   this->HP = 30;
   this->Atk = 70;
   this->Def = 5;
}

//attack by PC
void Merchant::attack(Player &pl) {
   pl.useOn(*this);
   if(pl.ifNeu()){//if attacked set to hositle
		pl.setNeu();
	}
}

//dtor
Merchant::~Merchant(){}
