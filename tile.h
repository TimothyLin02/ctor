#ifndef TILE_H
#define TILE_H

#include <vector>
#include <string>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::string;

class Edge;
class Vertice;

class Tile {
    int number;
    int type;
    int value;
    bool geese;
    vector<Vertice *> vertices;
    vector<Edge *> edges;
  public:
    Tile(int number);
    ~Tile();
    int getNumber();
    void setValue(int value);
    int getValue();
    void setType(int type);
    int getType();
    void initType(int type);
    void setGeese(bool geese);
    bool getGeese();
    vector<Vertice *> &getVertices();
    void addVertice(Vertice *vertice);
    vector<Edge *> &getEdges();
    void addEdge(Edge *edge);
    string strGeese();
    string strType();
    string strValue();
};

#endif

