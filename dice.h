#ifndef _DICE_H_
#define _DICE_H_

class Dice {
  public:
    virtual int roll() = 0;
    virtual ~Dice() = default;
};

#endif
