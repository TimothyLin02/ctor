#include "builder.h"
#include "builderId.h"
#include "housing.h"
#include "resourceType.h"
#include "road.h"
using std::string;
using std::vector;

Builder::Builder(int id, Dice *dice) : id{id}, dice{dice} {
    for (int i = 0; i < ResourceType::TOTAL; ++i) {
        numResources.push_back(0);
    }
}

Builder::~Builder() {
    for (size_t i = 0; i < housings.size(); i++) {
        delete housings[i];
    }
    for (size_t i = 0; i < roads.size(); i++) {
        delete roads[i];
    }
}

int Builder::getId() {
    return id;
}

void Builder::setDice(Dice *dice) {
    this->dice = dice;
}

Dice *Builder::getDice() {
    return dice;
}
vector<Housing *> &Builder::getHousings() {
    return housings;
}

vector<Road *> &Builder::getRoads() {
    return roads;
}

vector<int> &Builder::getNumResources() {
    return numResources;
}

string Builder::getName() {
    return BuilderId::names[id];
}

string Builder::getSymbol() {
    return BuilderId::symbols[id];
}

int Builder::totalResources() {
    int total = 0;
    for (int n = 0; n < ResourceType::TOTAL; ++n) {
        total += numResources[n];
    }
    return total;
}

void Builder::addResources(int type, int amount) {
    numResources[type] += amount;
}

void Builder::subResources(int type, int amount) {
    numResources[type] -= amount;
}

int Builder::getBuildingPoints() {
    int score = 0;
    for (std::size_t i = 0; i < housings.size(); ++i) {
        score += housings[i]->getType();
    }
    return score;
}

void Builder::addRoad(Road *newRoad) {
        roads.push_back(newRoad);
}

void Builder::addHousing(Housing *newRes) {
        housings.push_back(newRes);
}

