#ifndef _PERSISTANCE_H_
#define _PERSISTANCE_H_
#include <string>
using std::string;

class Builder;
class Board;
class Game;

class Persistence {
    Persistence();
  public:
    static Persistence *getInstance();
    Persistence(const Persistence &other) = delete;
    Persistence& operator=(const Persistence &other) = delete;

    Game *loadSavedGame(const char *savedGame);
    Board *loadSavedBoard(const char *savedBoard);

    void saveGame(Game *game, string fileName);
};

#endif
