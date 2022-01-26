#include "edge.h"
#include "vertice.h"
#include "tile.h"
#include "housing.h"
using std::vector;
using std::shared_ptr;
using std::string;

Vertice::Vertice(int number) : number{number}, housing{nullptr} {}

int Vertice::getNumber() {
    return number;
}

void Vertice::addTile(Tile *tile) {
    for (auto *t : tiles) {
        if (t->getNumber() == tile->getNumber()) {
            return;
        }
    }
    tiles.push_back(tile);
}

void Vertice::addEdge(Edge *edge) {
    for (auto *e : edges) {
        if (e->getNumber() == edge->getNumber()) {
            return;
        }
    }
    edges.push_back(edge);
}

vector<Edge *> &Vertice::getEdges() {
    return edges;
}

Housing *Vertice::getHousing() {
    return housing;
}

void Vertice::setHousing(Housing *housing) {
    this->housing = housing;
}

string Vertice::display() {
    return housing == nullptr ? std::to_string(number) : housing->display();
}

