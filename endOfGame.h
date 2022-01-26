#ifndef _END_OF_GAME_H_
#define _END_OF_GAME_H_
#include "gameplay.h"

class EndOfGame : public Gameplay {
  public:
    int play(Game *game) override;
};

#endif
