#include "edge.h"
#include "vertice.h"
#include "tile.h"
#include "road.h"
using std::vector;
using std::shared_ptr;
using std::string;

Edge::Edge(int number) : number{number}, road{nullptr} {}

int Edge::getNumber() { 
    return number;
}

void Edge::addTile(Tile *tile) {
    for (auto *t : tiles) {
        if (t->getNumber() == tile->getNumber()) {
            return;
        }
    }
    tiles.push_back(tile);
}

void Edge::addVertice(Vertice *vertice) {
    for (auto *v : vertices) {
        if (v->getNumber() == vertice->getNumber()) {
            return;
        }
    }
    vertices.push_back(vertice);
}

vector<Vertice *> &Edge::getVertices() {
    return vertices;
}

string Edge::display() {
    return (road == nullptr ? std::to_string(number) : road->display());
}

void Edge::setRoad(Road *addRoad) {
    road = addRoad;
}

Road *Edge::getRoad() {
	return road;
}
	
