#ifndef TILE_TYPE_H
#define TILE_TYPE_H

#include <string>
#include "resourceType.h"
using std::string;

#define TOTAL_TILE_TYPES 6
#define TOTAL_TILES 19

class TileType : public ResourceType {
  public:
    static const int PARK = 5;
    static const int TOTAL = TOTAL_TILE_TYPES;
    static const string names[TOTAL_TILE_TYPES];
};

#endif

