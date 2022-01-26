#ifndef _GAMEPLAY_TYPE_H_
#define _GAMEPLAY_TYPE_H_

#define TOTAL_GAMEPLAYS 4

class GameplayType {
  public:
    static const int BeginningOfGame = 0;
    static const int BeginningOfTurn = 1;
    static const int DuringTheTurn = 2;
    static const int EndOfGame = 3;

    static const int TOTAL = TOTAL_GAMEPLAYS;	
};

#endif
