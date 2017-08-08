#include "item.h"
#include "player.h"
using namespace std;

//ctor
Item::Item(string desc):isTaken(true) {
   this->name = desc;
	if (desc == "normal gold pile") {
      value = 1;
      ch = 'G';
   }
   if (desc == "small horde") {
      value = 2;
      ch = 'G';
   }
   if (desc == "merchant horde") {
      value = 4;
      ch = 'G';
   }
   if (desc == "dragon horde") {
      value = 6;
      ch = 'G';
      isTaken = false;
   }
   if (desc == "RH") {
      value = 10;      
      ch = 'P';
   }
   if (desc == "BA") {
      value = 5;
      ch = 'P';
   }
   if (desc == "BD") {
      value = 5;
      ch = 'P';
   }
   if (desc == "PH") {
      value = -10;       
      ch = 'P';
   }
   if (desc == "WA") {
      value = -5;
      ch = 'P';
   }
   if (desc == "WD") {
      value = -5;
      ch = 'P';
   }
}

//use this item on player
void Item::useOn(Player &pl) {
	if(this->ch == 'G'){
   	pl.addGold(value);
	}
	if(this->ch == 'P'){
      if ((name == "RH") or (name == "PH")) {
			pl.addHP(value);
      }
      else if ((name == "BA") or (name == "WA")) {
         pl.addAtk(value);
      }
      else if ((name == "BD") or (name == "WD")) {
         pl.addDef(value);
      }
   }
}

//return name of the item
string Item::getName() {
   return name;
}

//set isTaken to true
void Item::setTaken() {
   this->isTaken = true;
}

//return isTaken
bool Item::getTaken() {
   return isTaken;
}

//dtor
Item::~Item(){}
