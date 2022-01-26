#include "builderId.h"
#include "road.h"

Road::Road(int builderId, int edgeNum) : builderId{builderId}, edgeNum{edgeNum} {}

int Road::getBuilderId() {
    return builderId;
}

int Road::getEdgeNum() {
    return edgeNum;
}

string Road::display() {
    return BuilderId::symbols[builderId] + "R";
}

