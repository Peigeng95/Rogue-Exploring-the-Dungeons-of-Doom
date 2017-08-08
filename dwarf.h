#ifndef __DWARF_H__
#define __DWARF_H__

#include "player.h"

class Enemy;

class Dwarf: public Player {
   public:
		void addGold(int); //double gold!
      Dwarf();
      ~Dwarf();
};

#endif
