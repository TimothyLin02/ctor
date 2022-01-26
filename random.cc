#include "random.h"
using std::uniform_int_distribution;

Random::Random() {}

Random *Random::getInstance() {
    static Random random;
    return &random;
}

void Random::seed(unsigned seed) {
    generator.seed(seed);
}

int Random::getNumber(int min, int max) {
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}
