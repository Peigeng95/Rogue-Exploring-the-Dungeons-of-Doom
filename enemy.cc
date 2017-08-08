#include "enemy.h"
#include "player.h"
#include <cstdlib>

//ctor
Enemy::Enemy(): hostile(true) {}


//height and weight can be add from -1 to 1
void Enemy::autoMove(int &newh, int &neww) {
   newh = h + rand() % 3 - 1;
   neww = w + rand() % 3 - 1;
}


//type pass
void Enemy::attack(Player &pl) {
   pl.useOn(*this);
}

//all enemy's damage is calucated by the same function
void Enemy::useOn(Player &pl) {
   int dmg = this->Atk; 
   int def = pl.getDef();
   double total = ((100.0 / (100.0 + def)) * dmg);
   int PlHp = (int)total;
   pl.setHP(PlHp);
}

//see if it is hostile
bool Enemy::ifHost() {
   return this->hostile;
}

//dtor
Enemy::~Enemy(){}
