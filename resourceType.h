#ifndef RESOURCE_TYPE_H
#define RESOURCE_TYPE_H

#include <string>
using std::string;

#define TOTAL_RESOURCES 5

class ResourceType {
  public:
	static const int BRICK = 0;
	static const int ENERGY = 1;
	static const int GLASS = 2;
	static const int HEAT = 3;
	static const int WIFI = 4;

    static const int TOTAL = TOTAL_RESOURCES;	
	static const string names[TOTAL_RESOURCES];
};

#endif
