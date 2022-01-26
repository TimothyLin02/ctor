#include <fstream>
#include <iostream>
#include <string.h>
#include "board.h"
#include "builder.h"
#include "duringTheTurn.h"
#include "edge.h"
#include "exceptions.h"
#include "gameplayType.h"
#include "game.h"
#include "gameRule.h"
#include "housing.h"
#include "resourceType.h"
#include "road.h"
#include "tile.h"
#include "vertice.h"
#include "view.h"
#include "persistence.h"
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int DuringTheTurn::play(Game *game) {
    bool done = false;
    cout << game->getCurrentBuilder()->getName() << "'s during turn phase." << endl;
    while (!done) {
        Builder *builder = game->getCurrentBuilder();
        if (builder->getBuildingPoints() >= 10) {
            cout << "Congratulations! player " << builder->getName() << " won!" << endl;
            return GameplayType::EndOfGame;
        }
        cout << "? ";
        string command;
        std::cin >> command;
        if (cin.eof()) {
            Persistence::getInstance()->saveGame(game, "backup.sv");
            return -1;
        }
        if ("board" == command) {
	        View *view = View::getInstance();
	        view->printBoard(game->getBoard());
        } else if ("status" == command) {
	        View *view = View::getInstance();
	        vector<Builder *>builders = game->getBuilders();
	        for (size_t i = 0; i < builders.size(); i++) {
                view->printBuilder(builders[i]);
	        }
        } else if ("residences" == command) {
	        View *view = View::getInstance();
            Builder *builder = game->getCurrentBuilder();
            view->printResidences(builder);
        } else if ("build-road" == command) {
	        int roadNum;
            if (!(std::cin >> roadNum)) {
                cout << "That is not a number!" << endl;
                cin.clear();
                cin.ignore();
                if (cin.eof()) {
                    Persistence::getInstance()->saveGame(game, "backup.sv");
                    return -1;
                }
            } else if (roadNum < 0 || roadNum > 71) {
                cout << "That is not a valid edge!" << endl;
            } else {
                try {
                    Edge *edge = game->getBoard()->getEdges()[roadNum];
                    GameRule::getInstance()->buildRoad(builder, edge);
                    cout << "Road Built" << endl;
                } catch (NotEnoughResourceException &i) {
                    View *view = View::getInstance();
                    view->doNotHaveEnoughResources();
                } catch (NoConnectionToEdgeException &i) {
                    View *view = View::getInstance();
                    view->cannotBuildHere();
                } catch (AlreadyBuiltException &i) {
                    View *view = View::getInstance();
                    view->cannotBuildHere();
                }
            }
        } else if ("build-res" == command) {
            int resNum;
            if (!(std::cin >> resNum)) {
                cout << "That is not a number!" << endl;
                cin.clear();
                cin.ignore();
                if (cin.eof()) {
                    Persistence::getInstance()->saveGame(game, "backup.sv");
                    return -1;
                }
            } else if (resNum < 0 || resNum > 53) {
                cout << "That is not a valid vertice!" << endl;
            } else {
                try {
                    Vertice *vertice = game->getBoard()->getVertices()[resNum];
                    GameRule::getInstance()->buildBasement(builder, vertice);
                    cout << "Residence Built" << endl;
                } catch (NotEnoughResourceException &i) {
                    View *view = View::getInstance();
                    view->doNotHaveEnoughResources();
                } catch (NoRoadToVerticeException &i) {
                    View *view = View::getInstance();
                    view->cannotBuildHere();
                } catch (AlreadyBuiltException &i) {
                    View *view = View::getInstance();
                    view->cannotBuildHere();
                } catch (AdjacentResidenceException &i) {
                    View *view = View::getInstance();
                    view->cannotBuildHere();
                }
            }
        } else if ("improve" == command) {
            int resNum;
            if (!(std::cin >> resNum)) {
                cout << "That is not a number!" << endl;
                cin.clear();
                cin.ignore();
                if (cin.eof()) {
                    Persistence::getInstance()->saveGame(game, "backup.sv");
                    return -1;
                }
            } else if (resNum < 0 || resNum > 53) {
                cout << "That is not a valid vertice!" << endl;
            } else {
                try {
                    Vertice *vertice = game->getBoard()->getVertices()[resNum];
                    Housing *res = vertice->getHousing();
                    if (res != nullptr) {
                        int tier = res->getType();
                        if (tier == 1) {
                            GameRule::getInstance()->buildHouse(builder, vertice);
                            cout << "Successfully built house" << endl;
                        } else if (tier == 2) {
                            GameRule::getInstance()->buildTower(builder, vertice);
                            cout << "Successfully built tower" << endl;
                        }
                    } else {
                        throw NotOwnedException();
                    }
                } catch (NotEnoughResourceException &i) {
                    View *view = View::getInstance();
                    view->doNotHaveEnoughResources();
                } catch (NotOwnedException &i) {
                    View *view = View::getInstance();
                    view->cannotBuildHere();
                }
            }
        } else if ("next" == command) {
            done = true;
			game->nextCurrentBuilder();
			break;
        } else if ("trade" == command) {
            string colour;
            string give;
            string take;
            Builder *tradeBuilder = nullptr;
            int giveResource;
            int takeResource;
            cin >> colour;
            cin >> give;
            cin >> take;
            if (cin.eof()) {
                Persistence::getInstance()->saveGame(game, "backup.sv");
                return -1;
            }
            vector<Builder *>builders = game->getBuilders();
            for (size_t i = 0; i < builders.size(); i++) {
                if (colour == builders[i]->getName()) {
                     tradeBuilder =  builders[i];
                }
            }
            if (tradeBuilder == nullptr) {
                cout << "Not a valid player" << endl;
                continue;
            }
            if (builder->getName() == tradeBuilder->getName()) {
                cout << "Cannot trade with yourself" << endl;
                continue;
            }
            if (give == "Brick") {
                giveResource = ResourceType::BRICK;
            } else if (give == "Energy") {
                giveResource = ResourceType::ENERGY;
            } else if (give == "Glass") {
                giveResource = ResourceType::GLASS;
            } else if (give == "Heat") {
                giveResource = ResourceType::HEAT;
            } else if (give == "Wifi") {
                giveResource = ResourceType::WIFI;
            } else {
                cout << "Invalid give resource" << endl;
                continue;
            }
            if (take == "Brick") {
                takeResource = ResourceType::BRICK;
            } else if (take == "Energy") {
                takeResource = ResourceType::ENERGY;
            } else if (take == "Glass") {
                takeResource = ResourceType::GLASS;
            } else if (take == "Heat") {
                takeResource = ResourceType::HEAT;
            } else if (take == "Wifi") {
                takeResource = ResourceType::WIFI;
            } else {
                cout << "Invalid take resource" << endl;
                continue;
            }
            cout << builder->getName() << " offers " << tradeBuilder->getName();
            cout << " one " << give << " for one " << take << "." << endl;
            cout << "Does " << tradeBuilder->getName() << " accept this offer? (yes/no)" << endl;
            cout << "? ";
            string response;
            cin >> response;
            if (cin.eof()) {
                Persistence::getInstance()->saveGame(game, "backup.sv");
                return -1;
            }
            if (response == "no") {
                cout << tradeBuilder->getName() << " declines the offer" << endl;
                continue;
            } else if (response != "yes") {
                cout  << tradeBuilder->getName() << " declines since spelling is hard" << endl;
                continue;
            }
            try {
                GameRule::getInstance()->trade(builder, tradeBuilder, giveResource, takeResource);
                cout << "Trade Successful" << endl;
            } catch (NotEnoughResourceException &i) {
                View *view = View::getInstance();
                view->doNotHaveEnoughResources();
            }
        } else if ("save" == command) {
            string fileName;
            std::cin >> fileName;
            Persistence::getInstance()->saveGame(game, fileName);
        } else if ("help" == command) {
            cout << "Valid commands:" << endl;
            cout << "board" << endl;
            cout << "status" << endl;
            cout << "residences" << endl;
            cout << "build-road <edge#>" << endl;
            cout << "build-res <housing#>" << endl;
            cout << "improve <housing#>" << endl;
            cout << "build-road <edge#>" << endl;
            cout << "trade <colour> <give> <take>" << endl;
            cout << "next" << endl;
            cout << "save <file>" << endl;
            cout << "help" << endl;
        } else {
            View::invalidCommand();
        }
    }
    return GameplayType::BeginningOfTurn; 
}


