#ifndef _EDGE_H_
#define _EDGE_H_

#include <string>
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::string;

class Vertice;
class Tile;
class Road;

class Edge {
	int number;
	vector<Tile*> tiles;
	vector<Vertice*> vertices;
	Road *road;
  public:
    Edge(int number);
    int getNumber();
    void addTile(Tile *tile);
	void addVertice(Vertice *vertice);
	vector<Vertice *> &getVertices();
    Road *getRoad();
    void setRoad(Road *road);
	string display();
};

#endif
