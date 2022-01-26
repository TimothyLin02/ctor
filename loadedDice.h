#ifndef _LOADEDDICE_H_
#define _LOADEDDICE_H_

#include "dice.h"

class LoadedDice : public Dice {
  public:
    int roll() override;    
};

#endif
