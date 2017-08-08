#ifndef __ITEM_H__
#define __ITEM_H__

#include "cell.h"
#include <string>

class Player;

class Item: public Cell {
   double value;
   std::string name;
   bool isTaken;
   public:
      void useOn(Player &);
      Item(std::string);
      bool getTaken();
      std::string getName();
      void setTaken();
      ~Item();
};
#endif
   
