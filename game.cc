#include "gameFactory.h"
#include "builder.h"
#include "board.h"
#include "game.h"
#include "tile.h"
#include "loadedDice.h"
#include "fairDice.h"

Game::Game() : Game(new Board()) {}

Game::Game(Board *board) : board{board}, loadedDice{new LoadedDice()}, fairDice{new FairDice()} {
    builders.push_back(new Builder(BuilderId::Blue, fairDice));
    builders.push_back(new Builder(BuilderId::Red, fairDice));
    builders.push_back(new Builder(BuilderId::Orange, fairDice));
    builders.push_back(new Builder(BuilderId::Yellow, fairDice));
}

Game::~Game() {
    int size = builders.size();
    for (int i = 0; i < size; ++i) {
        delete builders[i];
    }
    delete loadedDice;
    delete fairDice;
    delete board;
}

Board *Game::getBoard() {
    return board;
}

Builder *Game::getCurrentBuilder() {
    return builders[curTurn]; 
}

vector<Builder *> &Game::getBuilders() {
    return builders;
}

void Game::nextCurrentBuilder() {
    curTurn = (curTurn + 1) % builders.size();
}

Dice *Game::getLoadedDice() {
    return loadedDice;
}

Dice *Game::getFairDice() {
    return fairDice;
}

void Game::setCurTurn(int turn) {
    curTurn = turn;
}

Tile *Game::getGeeseTile() {
    for (Tile *t : board->getTiles()) {
        if (t->getGeese()) {
            return t;
        }
    }
    return nullptr;
}

void Game::setCurStage(int curStage) {
    this->curStage = curStage;
}

int Game::getCurStage() {
    return curStage;
}

