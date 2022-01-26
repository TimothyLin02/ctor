#include <iostream>
#include "board.h"
#include "game.h"
#include "gameFactory.h"
#include "persistence.h"
#include "random.h"
#include "tile.h"
#include "tileType.h"

GameFactory::GameFactory() {}

GameFactory *GameFactory::getInstance() {
    static GameFactory gameFactory;
    return &gameFactory;
}

Game *GameFactory::newGame(Board *board) {
    Game *game = new Game(board);
    return game;
}

Game *GameFactory::newRandomGame() {
    Board *board = new Board();
    int tileTypes[] = {
        TileType::WIFI,
        TileType::WIFI,
        TileType::WIFI,
        TileType::HEAT,
        TileType::HEAT,
        TileType::HEAT,
        TileType::BRICK,
        TileType::BRICK,
        TileType::BRICK,
        TileType::BRICK,
        TileType::ENERGY,
        TileType::ENERGY,
        TileType::ENERGY,
        TileType::ENERGY,
        TileType::GLASS,
        TileType::GLASS,
        TileType::GLASS,
        TileType::GLASS,
        TileType::PARK,
    };
    int i = 0;
    for(; i < (int)board->getTiles().size(); ++i) {
        int t = 0;
        do {
            t = Random::getInstance()->getNumber(0, 18);
        } while (tileTypes[t] < 0);
        board->getTiles()[i]->initType(tileTypes[t]);
        tileTypes[t] = -1;
    }
    int tileValues[] = { // size is 18
        2, 12, 
        3, 3,
        4, 4,
        5, 5,
        6, 6,
        8, 8,
        9, 9,
        10, 10,
        11, 11
    };
    i = 0;
    for (; i < 18; ++i) {
        do {
            int t = Random::getInstance()->getNumber(0, 18);
            if (board->getTiles()[t]->getValue() == 0) {
                board->getTiles()[t]->setValue(tileValues[i]);
                tileValues[i] = 0;
            }
        } while (tileValues[i] != 0);
    }
    Game *game = new Game(board);
    return game;
}
