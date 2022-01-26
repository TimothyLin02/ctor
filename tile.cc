#include <iostream>
#include "tile.h"
#include "tileType.h"

Tile::Tile(int number) : number{number}, type{0}, value{0}, geese{false} {}

Tile::~Tile() {}

int Tile::getNumber() {
    return number;
}

void Tile::setValue(int value) {
    this->value = value;
}

int Tile::getValue() {
    return value;
}

void Tile::setGeese(bool geese) {
    this->geese = geese;
}

bool Tile::getGeese() {
    return geese;
}

string Tile::strGeese() {
    return (geese ? "GEESE" : "");
}

void Tile::setType(int type) {
    this->type = type;
}

int Tile::getType() {
    return type;
}

void Tile::initType(int type) {
    this->type = type;
    if (type == TileType::PARK) {
        geese = true;
        value = 7;
    }
}

string Tile::strType() {
    return TileType::names[type];
}

string Tile::strValue() {
    return value == 7 ? " " : std::to_string(value);
}

vector<Vertice *> &Tile::getVertices() {
    return vertices;
}

void Tile::addVertice(Vertice *vertice) {
    vertices.push_back(vertice);
}

vector<Edge *> &Tile::getEdges() {
    return edges;
}

void Tile::addEdge(Edge *edge) {
    edges.push_back(edge);
}

