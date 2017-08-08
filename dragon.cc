#include "dragon.h"
#include <cstdlib>
#include "item.h"

using namespace std;

//auto move
int temph, tempw;

//ctor
Dragon::Dragon():horde(NULL) {
   this->ch = 'D';
   this->HP = 150;
   this->Atk = 20;
   this->Def = 20;
}

//see if the dragon has a horde
bool Dragon::hashorde() {
	return (horde != NULL);
}

//set a horde for dragon
void Dragon::setH(Item *p) {
   this->horde = p;
}

//can this dragon pile be taken?
void Dragon::setTaken() {
   this->horde->setTaken();
}

//automove : must around the horde
void Dragon::autoMove(int &newh, int &neww) {
   temph = 0; tempw = 0;
   temph = h + rand() % 3 - 1;
   tempw = w + rand() % 3 - 1;
   for(;;){
   	if ((temph > horde->getH()+1) or (tempw > horde->getW()+1) or
       	(temph < horde->getH()-1) or (tempw < horde->getW()-1) or
       	((temph == h) and (tempw == w))){
       		temph = h + rand() % 3 - 1;
       		tempw = w + rand() % 3 - 1;
   	}
   	else break;
   }
   newh = temph;
   neww = tempw;
}

//dtor
Dragon::~Dragon() {}
