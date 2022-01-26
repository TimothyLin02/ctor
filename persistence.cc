#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "board.h"
#include "builder.h"
#include "edge.h"
#include "exceptions.h"
#include "game.h"
#include "housing.h"
#include "persistence.h"
#include "resourceType.h"
#include "road.h"
#include "tile.h"
#include "tileType.h"
#include "vertice.h"
using std::istream;
using std::ios_base;
using std::ifstream;
using std::cout;
using std::endl;
using std::getline;
using std::stoi;
using std::istringstream;
using std::string;

Persistence::Persistence() {}

Persistence *Persistence::getInstance() {
    static Persistence persistence;
    return &persistence;
}

Board *Persistence::loadSavedBoard(const char *savedBoard) {
    Board *board = new Board();
    istream *infile = nullptr;
    try {
        infile = new ifstream(savedBoard);
        infile->exceptions(ios_base::failbit);
    } catch( ios_base::failure ) {
        delete board;
        delete infile;
        throw ios_base::failure("could not open input file");
    }
    int i = 0;
    int type = 0;
    int value = 0;
    try {
        while (true) {
            *infile >> type >> value;
            board->setTileType(i++, type, value);
        }
    } catch( ios_base::failure ) {}
    delete infile;
    return board;
}

Game *Persistence::loadSavedGame(const char *savedGame) { 
    Board *board = new Board();
    istream *infile = nullptr;
    try {
        infile = new ifstream(savedGame);
        infile->exceptions(ios_base::failbit);
    } catch( ios_base::failure ) {
        delete board;
        delete infile;
        throw ios_base::failure("could not open input file");
    }
    int i = 0;
    int type = 0;
    int value = 0;
    int turn;
    try {
        string line;
        getline(*infile, line);
        istringstream ss{line};
        if (!(ss >> turn)) {
            throw InvalidSetupException{};
        }
        vector<string> builderInfo;
        for (int i = 0; i < 4; i++) {
            getline(*infile, line);
            std::size_t found = line.find_last_not_of(" ");
            if (found!=std::string::npos) {
                line.erase(found + 1);
            } else {
                line.clear();
            }
            builderInfo.push_back(line);
        }
        getline(*infile, line);
        istringstream ss2{line};
        while (ss2 >> type) {
            ss2 >> value;
            board->setTileType(i++, type, value);
        }
        Game *game = new Game(board);
        vector<Builder *> builders = game->getBuilders();
        game->setCurStage(1);
        game->setCurTurn(turn);
        for (size_t k = 0; k < builders.size(); k++) {
            Builder *builder = builders[k];
            string builderDesc = builderInfo[k];
            istringstream ss1{builderDesc};
            for (int j = 0; j < 5; j++) {
                int resourceAmount;
                if (ss1 >> resourceAmount) {
                    builders[k]->addResources(j, resourceAmount);
                } else {
                    throw InvalidBuilderSetupException{};
                }
            }
            string nextInput;
            ss1 >> nextInput;
            if (nextInput == "r") {
                while (true) {
                    ss1 >> nextInput;
                    if (nextInput == "h") {
                        break;
                    }
                    int location = stoi(nextInput);
                    Road *road = new Road(builder->getId(), location);
                    game->getBoard()->getEdges()[location]->setRoad(road);
                    builder->addRoad(road);
                }
            }
            while (!ss1.eof()) {
                int location;
                if (ss1 >> location) {
                    ss1 >> nextInput;
                    Housing *res = nullptr;
                    if (nextInput == "B") {
                        res = new Housing(1, builder, location);
                    } else if (nextInput == "H") {
                        res = new Housing(2, builder, location);
                    } else if (nextInput == "T") {
                        res = new Housing(3, builder, location);
                    } else {
                        throw InvalidBuilderSetupException{};
                    }
                    game->getBoard()->getVertices()[location]->setHousing(res);
                    builder->addHousing(res);
                } else {
                    throw InvalidBuilderSetupException{};
                }
            }
        }
        getline(*infile, line);
        int goose;
        istringstream ss3{line};
        if (ss3 >> goose) {
            vector<Tile *> tiles =  game->getBoard()->getTiles();
            for (size_t g = 0; g < tiles.size(); g++) {
                tiles[g]->setGeese(false);
            }
            tiles[goose]->setGeese(true);
        } else {
            throw InvalidSetupException{};
        }
        delete infile;
        return game;
    } catch( ios_base::failure ) {
    } catch (InvalidBuilderSetupException &i) {
        delete infile;
        delete board;
        throw InvalidBuilderSetupException{};
    } catch (InvalidSetupException &i) {
        delete infile;
        delete board;
        throw InvalidSetupException{};
    }
    delete infile;
    return nullptr;
}

void Persistence::saveGame(Game *game, string fileName) {
    std::ofstream file (fileName);
    if (file.is_open()) {
        vector<Builder *> builders = game->getBuilders();
        file << game->getCurrentBuilder()->getId() << endl;        
        for (size_t i = 0; i < builders.size(); i++) {        
            Builder *curBuilder = builders[i];
            vector<int> resources = curBuilder->getNumResources();
            file << resources[ResourceType::BRICK];
            file << " " << resources[ResourceType::ENERGY];
            file << " " << resources[ResourceType::GLASS];
            file << " " << resources[ResourceType::HEAT];
            file << " " << resources[ResourceType::WIFI];
            file << " r";
            vector<Road *> roads = curBuilder->getRoads();
            for (size_t j = 0; j < roads.size(); j++) {
                file << " " << roads[j]->getEdgeNum();
            }
            file << " h";
            vector<Housing *> res = curBuilder->getHousings();
            for (size_t j = 0; j < res.size(); j++) {
                file << " " << res[j]->getVerticeNum();
                if (res[j]->getType() == 3) {
                    file << " " << "T";
                } else if (res[j]->getType() == 2) {
                    file << " " << "H";
                } else if (res[j]->getType() == 1) {
                    file << " " << "B";
                }
            }
            file << endl;
        }
        vector<Tile *> tiles = game->getBoard()->getTiles();
        for (size_t i = 0; i < tiles.size(); i++) {
            if (i != 0) {
                file << " ";
            }
            file << tiles[i]->getType();
            file << " " << tiles[i]->getValue();
        }
        file << endl;
        for (size_t i = 0; i < tiles.size(); i++) {
            if (tiles[i]->getGeese()) {
                file << i << endl;
            }
        }
        file.close();
        cout << "successfully saved game into " << fileName << endl;
    } else {
        cout << "Unable to save to " << fileName << endl;
    }
}
