#ifndef _FAIRDICE_H_
#define _FAIRDICE_H_

#include "dice.h"

class FairDice : public Dice {
  public:
    int roll() override;    
};

#endif
