#ifndef _RANDOM_H_
#define _RANDOM_H_
#include <random>
using std::default_random_engine;

class Random {
    default_random_engine generator;
    Random();
  public:
    static Random *getInstance();
    Random(const Random &other) = delete;
    Random& operator=(const Random &other) = delete;
    int getNumber(int min, int max);
    void seed(unsigned seed);
};

#endif
