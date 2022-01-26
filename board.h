#ifndef _BOARD_H_
#define _BOARD_H_
#include <string>
#include <vector>

class Edge;
class Tile;
class Vertice;
using std::vector;

class Board {
    vector<Edge*> edges;
    vector<Tile*> tiles;
    vector<Vertice*> vertices;
    void linkVEToTiles();
    void linkVE();
  public:
    Board();
    ~Board();
    vector<Edge *> &getEdges();
    vector<Tile *> &getTiles();
    vector<Vertice *> &getVertices();
    void setTileType(int i, int type, int value);
};

#endif

