#ifndef _BEGINNING_OF_TURN_H_
#define _BEGINNING_OF_TURN_H_
#include <vector>
#include "gameplay.h"
using std::vector;

class Builder;
class Game;
class Tile;

class BeginningOfTurn : public Gameplay {
    void roll(Game *game, Builder *builder);
    void moveGeese(Game *game, Builder *builder);
    void collectResources(Builder *builder, vector<int> &resources);
    void distributeResources(Tile *tile, int (*gained)[4][19]);
  public:
    int play(Game *game) override;
};

#endif
