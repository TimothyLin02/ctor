#ifndef _BEGINNING_OF_GAME_H_
#define _BEGINNING_OF_GAME_H_
#include <vector>
#include "gameplay.h"
using std::vector;

class Builder;
class Vertice;

class BeginningOfGame : public Gameplay {
    void build(Builder *builder, vector<Vertice *> vertices);
  public:
    int play(Game *game) override;
};

#endif
