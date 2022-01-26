#include <iostream>
#include "beginningOfTurn.h"
#include "builder.h"
#include "board.h"
#include "dice.h"
#include "game.h"
#include "gameplayType.h"
#include "housing.h"
#include "random.h"
#include "resourceType.h"
#include "tile.h"
#include "vertice.h"
#include "view.h"
#include "persistence.h"
using std::cout;
using std::cin;
using std::endl;

int BeginningOfTurn::play(Game *game) {
    View::getInstance()->printBoard(game->getBoard());
    Builder *builder = game->getCurrentBuilder();
    cout << "Builder " << builder->getName() << "'s turn." << endl;
    View::getInstance()->printBuilder(builder);
    bool done = false;
    while (!done) {
        cout << "? ";
        string command;
        cin >> command;
        if (cin.eof()) {
            Persistence::getInstance()->saveGame(game, "backup.sv");
            return -1;
        }
        if (command == "load") {
            builder->setDice(game->getLoadedDice());
        } else if (command == "fair") {
            builder->setDice(game->getFairDice());
        } else if (command == "roll") {
            roll(game, builder);
            done = true;
        } else {
            View::invalidCommand();
        }
    }
    return GameplayType::DuringTheTurn; 
}

void BeginningOfTurn::roll(Game *game, Builder *builder) {
    size_t totalBuilders = game->getBuilders().size();
    const size_t totalTiles = 19;//game->getBoard()->getTiles().size();
    while (true) {
        int r = builder->getDice()->roll();
        if (r == 7) {
            moveGeese(game, builder);
            return;
        } else if (r >= 2 && r <= 12) {
            int gained[BuilderId::TOTAL][totalTiles];
            for (size_t b = 0; b < totalBuilders; ++b) {
                for (size_t t = 0; t < totalTiles; ++t) {
                    gained[b][t] = 0;
                }
            }
            for (size_t i = 0; i < totalTiles; ++i) {
                if (game->getBoard()->getTiles()[i]->getValue() == r) {
                    if (game->getBoard()->getTiles()[i]->getGeese() == true) {
                        continue;
                    }
                    distributeResources(game->getBoard()->getTiles()[i], &gained);
                }
            }
            int totalGained = 0;
            for (size_t b = 0; b < totalBuilders; ++b) {
                bool builderPrinted = false;
                for (size_t t = 0; t < totalTiles; ++t) {
                    if (gained[b][t] > 0) {
                        totalGained++;
                        game->getBuilders()[b]->addResources(t, gained[b][t]);
                        if (!builderPrinted) {
                            cout << "Builder " << game->getBuilders()[b]->getName();
                            cout << " gained:" << endl;
                            builderPrinted = true;
                        }
                        cout << gained[b][t] << " " << ResourceType::names[t] << endl;
                    }
                }
            }
            if (totalGained == 0) {
                cout << "No builders gained resources." << endl;
            }
            return;
        } else {
            cout << "Invalid roll." << endl;
        }
    }
}

void BeginningOfTurn::moveGeese(Game *game, Builder *builder) {
    string line;
    Tile *tile = game->getGeeseTile();
    //use array to eliminate duplications.
    vector<Builder *> builders(game->getBuilders().size());
    vector<Vertice *> vertices = tile->getVertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i]->getHousing() != nullptr) {
            Builder *builder = vertices[i]->getHousing()->getBuilder();
            if (builder->totalResources() >= 10) {
                // index can handle duplications automatically.
                builders[builder->getId()] = builder;
            }
        }
    }

    //lose resources
    for (size_t i = 0; i < builders.size(); ++i) {
        if (builders[i] != nullptr) {
            vector<int> resources;
            collectResources(builders[i], resources);
            vector<int> numResources;
            for (int r = 0; r < ResourceType::TOTAL; ++r) {
                numResources.push_back(builders[i]->getNumResources()[r]);
            }
            int half = resources.size() / 2;
            int r = 0;
            for (int n = 0; n < half; ++n) {
                do {
                    r = Random::getInstance()->getNumber(0, resources.size() - 1);
                } while (resources[r] == -1);
                resources[r] = -1;
            }

            //reset to 0
            for (r = 0; r < (int)builders[i]->getNumResources().size(); ++r) {
                builders[i]->getNumResources()[r] = 0;
            }
            
            //recount each resource
            for (int n = 0; n < (int)resources.size(); ++n) {
                if (resources[n] != -1) {
                    builders[i]->getNumResources()[resources[n]]++;
                }
            }
            
            //calc losts
            int losts = 0;
            for (r = 0; r < (int)numResources.size(); ++r) {
                numResources[r] -= builders[i]->getNumResources()[r];
                losts += numResources[r];
            }

            cout << "Builder " << builders[i]->getName() << " loses " << losts;
            cout << " resources to the geese. They lose:" << endl;
            for (r = 0; r < (int)numResources.size(); ++r) {
                if (numResources[r] > 0) {
                    cout << numResources[r] << " " << ResourceType::names[r] << endl;
                }
            }
        }
    }
    int newTile = -1;
    while (true) {
        cout << "Choose where to place the GEESE." << endl;
        try {
            int t;
            cin >> t;
            if (cin.eof()) {
                Persistence::getInstance()->saveGame(game, "backup.sv");
                return;
            }
            if (t != tile->getNumber() && t >= 0 &&
                t < (int)game->getBoard()->getTiles().size()) {
                newTile = t;
                break;
            }    
        }
        catch (...) {
            View::invalidCommand();
        }
    }
    
    //steal
    tile->setGeese(false);
    tile = game->getBoard()->getTiles()[newTile];
    tile->setGeese(true);
    vector<bool> hasRs(game->getBuilders().size());
    bool found = false;
    vertices = tile->getVertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i]->getHousing() != nullptr &&
            vertices[i]->getHousing()->getBuilder()->getId() != builder->getId() &&
            vertices[i]->getHousing()->getBuilder()->totalResources() > 0) {
                int b = vertices[i]->getHousing()->getBuilder()->getId();
                hasRs[b] = true;
                found = true;
                builders[b] = game->getBuilders()[b];
        }
    }
    if (found) {
        cout << "Builder " << builder->getName() << " can choose to steal from ";
        bool first = true;
        for (int i = 0; i < (int)hasRs.size(); ++i) {
            if (hasRs[i]) {
                if (!first) {
                    cout << ",";
                }
                cout << BuilderId::names[i];
                first = false;
            }
        }
        cout << "." << endl;
        Builder *from;
        while (true) {
            try {
                cout << "Choose a builder to steal from." << endl;
                string name;
                cin >> name;
                if (cin.eof()) {
                    Persistence::getInstance()->saveGame(game, "backup.sv");
                    return;
                }
                int fromId = BuilderId::nameToId(name);
                if (fromId != -1) { 
                    from = builders[fromId];
                    break;
                }
            }
            catch(...) {
                View::invalidCommand();
            }
        }
        vector<int> resources;
        collectResources(from, resources);
        int r = Random::getInstance()->getNumber(0, resources.size() - 1);
        from->subResources(resources[r], 1); 
        builder->addResources(resources[r], 1); 
        cout << "Builder " << builder->getName();
        cout << " steals " << ResourceType::names[resources[r]];
        cout << " from builder " << from->getName() << "." << endl;
    } else {
        cout << "Builder " << builder->getName();
        cout << " has no builders to steal from." << endl; 
    }
}

void BeginningOfTurn::collectResources(Builder *builder, vector<int> &resources) {
    for (int i = 0; i < ResourceType::TOTAL; ++i) {
        for (int n = 0; n < builder->getNumResources()[i]; ++n) {
            resources.push_back(i);
        }
    }
}

void BeginningOfTurn::distributeResources(Tile *tile, int (*gained)[4][19]) {
    int size = tile->getVertices().size();
    vector<Vertice *> vertices = tile->getVertices();
    for (int i = 0; i < size; ++i) {
        Housing *housing = vertices[i]->getHousing();
        if (housing != nullptr) {
            (*gained)[housing->getBuilder()->getId()][tile->getType()] += housing->getType();
        }
    }
}

