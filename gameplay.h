#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_
#include "gameplayType.h"

class Game;

class Gameplay {
  public:
    virtual int play(Game *game) = 0;
    virtual ~Gameplay() = default;
};

#endif
