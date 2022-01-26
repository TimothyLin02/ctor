#ifndef _DURING_THE_TURN_H_
#define _DURING_THE_TURN_H_
#include "gameplay.h"

class DuringTheTurn : public Gameplay {
  public:
      //takes in commands for during the game.
      int play(Game *game) override;
};

#endif
