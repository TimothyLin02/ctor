#ifndef HOUSING_TYPE_H
#define HOUSING_TYPE_H

#include <string>
using std::string;

#define TOTAL_HOUSINGS 4

class HousingType {
  public:
    static const int E = 0; // empty
	static const int B = 1;
	static const int H = 2; 
	static const int T = 3;

    static const int TOTAL = TOTAL_HOUSINGS;	
	static const string names[TOTAL_HOUSINGS];
    static int nameToId(string &name);
};

#endif
