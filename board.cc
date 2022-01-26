#include "board.h"
#include "edge.h"
#include "tile.h"
#include "vertice.h"

Board::Board() {
    for (int i = 0; i < 54; ++i) {
        vertices.push_back(new Vertice(i));
    }
    for (int i = 0; i < 72; ++i) {
        edges.push_back(new Edge(i));
    }
    for (int i = 0; i < 19; ++i) {
        tiles.push_back(new Tile(i));
    }

    // setup links
    tiles[0]->addVertice(vertices[0]);
    tiles[0]->addVertice(vertices[1]);
    tiles[0]->addVertice(vertices[3]);
    tiles[0]->addVertice(vertices[4]);
    tiles[0]->addVertice(vertices[8]);
    tiles[0]->addVertice(vertices[9]);
    tiles[0]->addEdge(edges[0]);
    tiles[0]->addEdge(edges[1]);
    tiles[0]->addEdge(edges[2]);
    tiles[0]->addEdge(edges[6]);
    tiles[0]->addEdge(edges[7]);
    tiles[0]->addEdge(edges[10]);

    int v = 2, e = 3;
    tiles[1]->addVertice(vertices[v]);
    tiles[1]->addVertice(vertices[v+1]);
    tiles[1]->addVertice(vertices[v+5]);
    tiles[1]->addVertice(vertices[v+6]);
    tiles[1]->addVertice(vertices[v+11]);
    tiles[1]->addVertice(vertices[v+12]);
    tiles[1]->addEdge(edges[e]);
    tiles[1]->addEdge(edges[e+2]);
    tiles[1]->addEdge(edges[e+3]);
    tiles[1]->addEdge(edges[e+10]);
    tiles[1]->addEdge(edges[e+11]);
    tiles[1]->addEdge(edges[e+15]);
        
    v = 4; e = 4;
    tiles[2]->addVertice(vertices[v]);
    tiles[2]->addVertice(vertices[v+1]);
    tiles[2]->addVertice(vertices[v+5]);
    tiles[2]->addVertice(vertices[v+6]);
    tiles[2]->addVertice(vertices[v+11]);
    tiles[2]->addVertice(vertices[v+12]);
    tiles[2]->addEdge(edges[e]);
    tiles[2]->addEdge(edges[e+3]);
    tiles[2]->addEdge(edges[e+4]);
    tiles[2]->addEdge(edges[e+11]);
    tiles[2]->addEdge(edges[e+12]);
    tiles[2]->addEdge(edges[e+15]);

    v = 6; e = 9;
    for (int i = 3; i <= 13; i += 5) {
        tiles[i]->addVertice(vertices[v]);
        tiles[i]->addVertice(vertices[v+1]);
        tiles[i]->addVertice(vertices[v+6]);
        tiles[i]->addVertice(vertices[v+7]);
        tiles[i]->addVertice(vertices[v+12]);
        tiles[i]->addVertice(vertices[v+13]);
        tiles[i]->addEdge(edges[e]);
        tiles[i]->addEdge(edges[e+3]);
        tiles[i]->addEdge(edges[e+4]);
        tiles[i]->addEdge(edges[e+11]);
        tiles[i]->addEdge(edges[e+12]);
        tiles[i]->addEdge(edges[e+17]);

        v += 2; e += 1;
        tiles[i+1]->addVertice(vertices[v]);
        tiles[i+1]->addVertice(vertices[v+1]);
        tiles[i+1]->addVertice(vertices[v+6]);
        tiles[i+1]->addVertice(vertices[v+7]);
        tiles[i+1]->addVertice(vertices[v+12]);
        tiles[i+1]->addVertice(vertices[v+13]);
        tiles[i+1]->addEdge(edges[e]);
        tiles[i+1]->addEdge(edges[e+4]);
        tiles[i+1]->addEdge(edges[e+5]);
        tiles[i+1]->addEdge(edges[e+12]);
        tiles[i+1]->addEdge(edges[e+13]);
        tiles[i+1]->addEdge(edges[e+17]);
            
        v += 2; e += 1;
        tiles[i+2]->addVertice(vertices[v]);
        tiles[i+2]->addVertice(vertices[v+1]);
        tiles[i+2]->addVertice(vertices[v+6]);
        tiles[i+2]->addVertice(vertices[v+7]);
        tiles[i+2]->addVertice(vertices[v+12]);
        tiles[i+2]->addVertice(vertices[v+13]);
        tiles[i+2]->addEdge(edges[e]);
        tiles[i+2]->addEdge(edges[e+5]);
        tiles[i+2]->addEdge(edges[e+6]);
        tiles[i+2]->addEdge(edges[e+13]);
        tiles[i+2]->addEdge(edges[e+14]);
        tiles[i+2]->addEdge(edges[e+17]);
        
        v += 8; e += 15;
    }
        
    v = 13; e = 18;
    for (int i=6; i<16; i+=5) {
        tiles[i]->addVertice(vertices[v]);
        tiles[i]->addVertice(vertices[v+1]);
        tiles[i]->addVertice(vertices[v+6]);
        tiles[i]->addVertice(vertices[v+7]);
        tiles[i]->addVertice(vertices[v+12]);
        tiles[i]->addVertice(vertices[v+13]);
        tiles[i]->addEdge(edges[e]);
        tiles[i]->addEdge(edges[e+3]);
        tiles[i]->addEdge(edges[e+4]);
        tiles[i]->addEdge(edges[e+12]);
        tiles[i]->addEdge(edges[e+13]);
        tiles[i]->addEdge(edges[e+17]);

        v += 2; e += 1;
        tiles[i+1]->addVertice(vertices[v]);
        tiles[i+1]->addVertice(vertices[v+1]);
        tiles[i+1]->addVertice(vertices[v+6]);
        tiles[i+1]->addVertice(vertices[v+7]);
        tiles[i+1]->addVertice(vertices[v+12]);
        tiles[i+1]->addVertice(vertices[v+13]);
        tiles[i+1]->addEdge(edges[e]);
        tiles[i+1]->addEdge(edges[e+4]);
        tiles[i+1]->addEdge(edges[e+5]);
        tiles[i+1]->addEdge(edges[e+13]);
        tiles[i+1]->addEdge(edges[e+14]);
        tiles[i+1]->addEdge(edges[e+17]);

        //v += 12; e += 17;
        v += 10; e += 16;
    }

       v = 37; e = 52;
    tiles[16]->addVertice(vertices[v]);
    tiles[16]->addVertice(vertices[v+1]);
    tiles[16]->addVertice(vertices[v+6]);
    tiles[16]->addVertice(vertices[v+7]);
    tiles[16]->addVertice(vertices[v+11]);
    tiles[16]->addVertice(vertices[v+12]);
    tiles[16]->addEdge(edges[e]);
    tiles[16]->addEdge(edges[e+3]);
    tiles[16]->addEdge(edges[e+4]);
    tiles[16]->addEdge(edges[e+11]);
    tiles[16]->addEdge(edges[e+12]);
    tiles[16]->addEdge(edges[e+15]);

    v = 39; e = 53;
    tiles[17]->addVertice(vertices[v]);
    tiles[17]->addVertice(vertices[v+1]);
    tiles[17]->addVertice(vertices[v+6]);
    tiles[17]->addVertice(vertices[v+7]);
    tiles[17]->addVertice(vertices[v+11]);
    tiles[17]->addVertice(vertices[v+12]);
    tiles[17]->addEdge(edges[e]);
    tiles[17]->addEdge(edges[e+4]);
    tiles[17]->addEdge(edges[e+5]);
    tiles[17]->addEdge(edges[e+12]);
    tiles[17]->addEdge(edges[e+13]);
    tiles[17]->addEdge(edges[e+15]);
    
    v = 44; e = 61;
    tiles[18]->addVertice(vertices[v]);
    tiles[18]->addVertice(vertices[v+1]);
    tiles[18]->addVertice(vertices[v+5]);
    tiles[18]->addVertice(vertices[v+6]);
    tiles[18]->addVertice(vertices[v+8]);
    tiles[18]->addVertice(vertices[v+9]);
    tiles[18]->addEdge(edges[e]);
    tiles[18]->addEdge(edges[e+3]);
    tiles[18]->addEdge(edges[e+4]);
    tiles[18]->addEdge(edges[e+8]);
    tiles[18]->addEdge(edges[e+9]);
    tiles[18]->addEdge(edges[e+10]);
        
    linkVEToTiles();
    linkVE();
}

Board::~Board() {
    int size = vertices.size();
    for (int i = 0; i < size; ++i) {
        delete vertices[i];  
    }
    size = edges.size();
    for (int i = 0; i < size; ++i) {
        delete edges[i];  
    }
    size = tiles.size();
    for (int i = 0; i < size; ++i) {
        delete tiles[i];  
    }
}
    
void Board::linkVEToTiles() {
    for (Tile *tile : tiles) {
        for (Edge *edge : tile->getEdges()) {
            edge->addTile(tile);
        }
        for (Vertice *vertice : tile->getVertices()) {
            vertice->addTile(tile);
        }
    }
}

void Board::linkVE() {
    for (Tile *tile : tiles) {
        // top left corner
        tile->getVertices()[0]->addEdge(tile->getEdges()[0]);
        tile->getVertices()[0]->addEdge(tile->getEdges()[1]);
        tile->getEdges()[0]->addVertice(tile->getVertices()[0]);
        tile->getEdges()[1]->addVertice(tile->getVertices()[0]);

        // top right corner
        tile->getVertices()[1]->addEdge(tile->getEdges()[0]);
        tile->getVertices()[1]->addEdge(tile->getEdges()[2]);
        tile->getEdges()[0]->addVertice(tile->getVertices()[1]);
        tile->getEdges()[2]->addVertice(tile->getVertices()[1]);

        // middle left
        tile->getVertices()[2]->addEdge(tile->getEdges()[1]);
        tile->getVertices()[2]->addEdge(tile->getEdges()[3]);
        tile->getEdges()[1]->addVertice(tile->getVertices()[2]);
        tile->getEdges()[3]->addVertice(tile->getVertices()[2]);

        // middle right
        tile->getVertices()[3]->addEdge(tile->getEdges()[2]);
        tile->getVertices()[3]->addEdge(tile->getEdges()[4]);
        tile->getEdges()[2]->addVertice(tile->getVertices()[3]);
        tile->getEdges()[4]->addVertice(tile->getVertices()[3]);

        // bottom left corner
        tile->getVertices()[4]->addEdge(tile->getEdges()[3]);
        tile->getVertices()[4]->addEdge(tile->getEdges()[5]);
        tile->getEdges()[3]->addVertice(tile->getVertices()[4]);
        tile->getEdges()[5]->addVertice(tile->getVertices()[4]);

        // bottom right corner
        tile->getVertices()[5]->addEdge(tile->getEdges()[4]);
        tile->getVertices()[5]->addEdge(tile->getEdges()[5]);
        tile->getEdges()[4]->addVertice(tile->getVertices()[5]);
        tile->getEdges()[5]->addVertice(tile->getVertices()[5]);
    }
}

vector<Vertice *> &Board::getVertices() {
    return vertices;
}

vector<Edge *> &Board::getEdges() {
    return edges;
}

vector<Tile *> &Board::getTiles() {
    return tiles;
}

void Board::setTileType(int i, int type, int value) {
    tiles[i]->setType(type);
    tiles[i]->setValue(value);
    if (value == 7) {
        tiles[i]->setGeese(true);
    }
}
