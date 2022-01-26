#ifndef ROAD_H
#define ROAD_H
#include <iostream>
#include <string>
using std::string;

class Road {
    int builderId;
    int edgeNum;

  public:
    Road(int builderId, int edgeNum);
    
    // Returns the builder's ID number
    int getBuilderId();

    // Returns the edge's number
    int getEdgeNum();

    // Displays the road
    string display();
};

#endif
