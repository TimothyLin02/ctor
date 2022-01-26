#include <iostream>
#include <cstring>
#include <string>
#include "board.h"
#include "game.h"
#include "gameController.h"
#include "gameFactory.h"
#include "persistence.h"
#include "random.h"
#include "view.h"
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    char* savedGame = nullptr;
    char* savedBoard = nullptr;
    bool randomBoard = false;

    for (int i = 0; i < argc; ++i) {
        if (strcmp("-seed", argv[i]) == 0) {
            i++;
            unsigned seed = strtol(argv[i], nullptr, 10);
            cout << "seed: " << seed << endl;
            Random::getInstance()->seed(seed);
        }
        else if (strcmp("-load", argv[i]) == 0) {
            i++;
            savedGame = argv[i];
            savedBoard = nullptr;
        }
        else if (strcmp("-board", argv[i]) == 0) {
            i++;
            savedGame = nullptr;
            savedBoard = argv[i];
        }
        else if (strcmp("-random-board", argv[i]) == 0) {
            randomBoard = true;
        }
    }

    Game *game = nullptr;
    if (savedGame != nullptr) {
        game = Persistence::getInstance()->loadSavedGame(savedGame);
    }
    else if (savedBoard != nullptr) {
        game = GameFactory::getInstance()->newGame(
            Persistence::getInstance()->loadSavedBoard(savedBoard));
    }
    else if (randomBoard) {
        game = GameFactory::getInstance()->newRandomGame();
    }
    else {
        Board *board = nullptr;
        try {
            board = Persistence::getInstance()->loadSavedBoard("layout.txt");
        } catch (...) {
        }
        if (board == nullptr) {
            game = GameFactory::getInstance()->newRandomGame();
        }
        else {
            game = GameFactory::getInstance()->newGame(board);
        }
    }

    try {
        while (game) {
            GameController::getInstance()->play(game);
            game = nullptr;
            if (std::cin.eof()) {
                break;
            }
            cout << "Would you like to play again?" << endl;
            string input;
            while (std::cin >> input) {
                if (input == "yes") {
                    game = GameFactory::getInstance()->newRandomGame();
                    break;
                } else if (input == "no") {
                    break;
                } else {
                    cout << "Please enter yes to play again or no to quit" << endl;
                }
            }
        }
    } catch (...) {
        cout << "play crashed! Terminate the game" << endl;
    }
    return 0;
}
