#ifndef GAMERULE_H
#define GAMERULE_H

#include <vector>
#include <string>
#include <memory>

using std::vector;
using std::string;

class Builder;
class Vertice;
class Edge;

class GameRule {
    GameRule();
    bool noAdjHousing(Vertice *vertice);
    bool ownRoad(int builder, Vertice *vertice);
    bool canBuildRoad(Builder *builder, Edge *edge);
  public:
    static GameRule *getInstance();
    GameRule(const GameRule &other) = delete;
    GameRule& operator=(const GameRule &other) = delete;
    void buildBasementFree(Builder *builder, Vertice *vertice);
    void buildBasement(Builder *builder, Vertice *vertice); //NotEnoughResourceException, AlreadyBuiltException, AjacentResidenceException, NoRoadToVerticeException
    void buildHouse(Builder *builder, Vertice *vertice);
    void buildTower(Builder *builder, Vertice *vertice);
    void buildRoad(Builder *builder, Edge *edge);
    void trade(Builder *builder, Builder *tradeBuilder, int giveResource, int takeResource);
};

#endif
