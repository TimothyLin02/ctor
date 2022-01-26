#include "housingType.h"

const std::string HousingType::names[] = {"", "B", "H", "T"};

int HousingType::nameToId(string &name) {
    for (int i = 0; i < TOTAL; i++) {
        if (name == names[i]) {
            return i;
        }
    }
    return 0;
}

