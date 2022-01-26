#include <iostream>
#include <random>
#include <vector>
#include "fairDice.h"
#include "random.h"

int FairDice::roll() {
    int diceRoll = Random::getInstance()->getNumber(1, 6) +
                   Random::getInstance()->getNumber(1, 6);
    std::cout << "fair roll: " << diceRoll << std::endl;
    return diceRoll;
    /*return Random::getInstance()->getNumber(1, 6) + 
           Random::getInstance()->getNumber(1, 6);*/
}
