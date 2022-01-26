#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include "gameplayType.h"
#include "builderId.h"
using std::vector;

class Board;
class Tile;
class Builder;
class Dice;

class Game {
    Board *board;
    
    Dice *loadedDice;
    Dice *fairDice;
    
    vector<Builder *> builders;

    int curStage = GameplayType::BeginningOfGame;
    int curTurn = BuilderId::Blue;

  public:
    Game();
    Game(Board *board);
    ~Game();
        
    Board *getBoard();

    vector<Builder *> &getBuilders();
    Builder *getCurrentBuilder();

    void setCurTurn(int turn);

    void nextCurrentBuilder();
    
    Dice *getLoadedDice();
    Dice *getFairDice();

    Tile *getGeeseTile();

    void setCurStage(int curStage);
    int getCurStage();
};

#endif

