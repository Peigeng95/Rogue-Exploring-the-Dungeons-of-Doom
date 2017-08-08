#include "character.h"

using namespace std;

//ctor
Character::Character(){}

//return Heal point
int Character::getHP(){
   return this->HP;
}

//return attack
int Character::getAtk(){
   return this->Atk;
}

//return defence
int Character::getDef(){
   return this->Def;
}

//return set heal point after being attack
void Character::setHP(int damage) {
   this->HP = this->HP - damage;
}

//check if this character is dead ( HP < 0 )
bool Character::isdead() {
   if(HP > 0){
      return false;
   }
   else{
		HP = 0;
      return true;
   }
}

//dtor
Character::~Character(){}
