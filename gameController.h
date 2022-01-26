#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include <vector>
#include "gameplayType.h"
using std::vector;

class Game;
class Gameplay;

class GameController {
    GameController();
    Game *game;
    vector<Gameplay *> stages;
    Gameplay *curStage;

  public:
    static GameController *getInstance();
    GameController(const GameController &other) = delete;
    GameController& operator=(const GameController &other) = delete;
    ~GameController();
    void play(Game *game);
};

#endif
