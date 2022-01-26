#ifndef _GAME_FACTORY_H_
#define _GAME_FACTORY_H_

class Board;
class Game;

class GameFactory {
    GameFactory();
  public:
    static GameFactory *getInstance();
    GameFactory(const GameFactory &other) = delete;
    GameFactory& operator=(const GameFactory &other) = delete;

    Game *newGame(Board *board);
    Game *newRandomGame();
};

#endif
