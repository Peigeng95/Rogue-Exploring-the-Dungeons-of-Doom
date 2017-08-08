#include "player.h"
#include "enemy.h"
#include "vampire.h"
#include "goblin.h"

using namespace std;

//ctor
Player::Player():gold(0), neutral(true){
   this->ch = '@';
}

//return gold they have
double Player::getGold() {
   return this->gold;
}

//return the charator race
char Player::getRole() {
   return this->role;
}

//return if it is neutral
bool Player::ifNeu() {
   return this->neutral;
}

//set this enemy to be hositle
void Player::setNeu() {
   this->neutral = !neutral;
}

//type pass
void Player::attack(Enemy &en) {
   en.useOn(*this);
}

//attack normal enemy
void Player::useOn(Enemy &en) {
   int dmg = this->Atk; 
   int def = en.getDef();
   double total = ((100.0 / (100.0 + def)) * dmg);
   int EnHp = (int)total;
   en.setHP(EnHp);
}

//attack Goblin which steal golds
void Player::useOn(Goblin &N) {
   int dmg = this->Atk; 
   int def = N.getDef();
   double total = ((100.0 / (100.0 + def)) * dmg);
   int EnHp = (int)total;
   N.setHP(EnHp);
	this->gold = this->gold - 1;//steal 0.5 gold
	N.addGoldsteal(1);
}

//attack Vampire which steal health
void Player::useOn(Vampire &V) {
   int dmg = this->Atk; 
   int def = V.getDef();
   double total = ((100.0 / (100.0 + def)) * dmg);
   int EnHp = (int)total - 3; //each attack steal 3 heal point
   V.setHP(EnHp);
}

//add Gold to player
void Player::addGold(double n) {
   this->gold = this->gold + n;
}

//if player is dead
bool Player::GameOver() {
	return (this->HP <= 0);
}

//reset player to have no poition
void Player::reset() {
   Atk = defAtk;
   Def = defDef;
}

//add heal point
void Player::addHP(int value) {
   HP += value;
   if (HP > this->maxHP)
      HP = maxHP;
}

//add attack
void Player::addAtk(int value) {
   Atk += value;
}

//add defence
void Player::addDef(int value) {
   Def += value;
}

//dtor
Player::~Player() {}
