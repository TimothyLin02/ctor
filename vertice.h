#ifndef VERTICE_H
#define VERTICE_H

#include <vector>
#include <string>
#include <memory>

using std::vector;
using std::string;

class Tile;
class Edge;
class Housing;

class Vertice {
    int number;
    vector<Tile *> tiles;
    vector<Edge *> edges;
    Housing *housing;
  public:
    Vertice(int number);
    int getNumber();
    void addTile(Tile *tile);
    void addEdge(Edge *edge);
    vector<Edge *> &getEdges();
    Housing *getHousing();
    void setHousing(Housing *housing);
    string display();
};

#endif

