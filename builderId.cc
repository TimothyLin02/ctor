#include "builderId.h"

const std::string BuilderId::names[] = {"Blue", "Red", "Orange", "Yellow" };
const std::string BuilderId::symbols[] = {"B", "R", "O", "Y"};

int BuilderId::nameToId(string name) {
    for (int i = 0; i < TOTAL; ++i) {
        if (name == names[i]) {
            return i;
        }
    }
    return -1;
}
    
int BuilderId::symbolToId(string symbol) {
    for (int i = 0; i < TOTAL; ++i) {
        if (symbol == symbols[i]) {
            return i;
        }
    }
    return -1;
}

