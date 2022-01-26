#include "gameController.h"
#include "beginningOfGame.h"
#include "beginningOfTurn.h"
#include "duringTheTurn.h"
#include "endOfGame.h"
#include "game.h"

GameController *GameController::getInstance() {
    static GameController gameController;
    return &gameController;
}

GameController::GameController() : game{nullptr} {
    stages.push_back(new BeginningOfGame());
    stages.push_back(new BeginningOfTurn());
    stages.push_back(new DuringTheTurn());
    stages.push_back(new EndOfGame());
    //curStage = stages[game->getCurStage()];
}

GameController::~GameController() {
    for (size_t i = 0; i < stages.size(); ++i) {
        delete stages[i];
    }
    delete game;
}

void GameController::play(Game *game) {
    if (this->game != nullptr) {
        delete this->game;
    }
    this->game = game;
    curStage = stages[game->getCurStage()];
    while (curStage != nullptr) {
        int next = curStage->play(game);
        if (next < 0 || next >= (int)stages.size()) {
            curStage = nullptr;
        } else {
            curStage = stages[next];
        }
    }
}

