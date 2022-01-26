#include "beginningOfGame.h"
#include "board.h"
#include "builder.h"
#include "exceptions.h"
#include "game.h"
#include "gameplayType.h"
#include "gameRule.h"
#include <iostream>
#include "vertice.h"
#include "view.h"
using std::cout;
using std::cin;
using std::endl;

void BeginningOfGame::build(Builder *builder, vector<Vertice *> vertices) {
    while(true) {
        cout << "Builder " << builder->getName();
        cout << ", where do you want to build a basement?" << endl;
        cout << "? ";
        try {
            int v;
            if (!(cin >> v) || !(v >= 0 && v <= 53)) {
                View::invalidInput();
                cin.clear();
                cin.ignore();
            } else {
                GameRule::getInstance()->buildBasementFree(builder, vertices[v]);
                return;
            }
        } catch (InvalidSetupException) {
            throw InvalidSetupException{};    
        } catch (AlreadyBuiltException) {
            View::cannotBuildHere();
        } catch (...) {
            View::invalidCommand();
        }
    }
}

int BeginningOfGame::play(Game *game) {
    View::getInstance()->printBoard(game->getBoard());
    int i = 0;
    int builders = game->getBuilders().size();
    for (; i < builders; ++i) {
        build(game->getBuilders()[i], game->getBoard()->getVertices());
    }
    i--;
    for (; i >= 0; --i) {
        build(game->getBuilders()[i], game->getBoard()->getVertices());
    }
    return GameplayType::BeginningOfTurn; 
}

