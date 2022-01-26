#ifndef BUILDERID_H
#define BUILDERID_H

#include <string>
using std::string;

#define TOTAL_BUILDERS 4

class BuilderId {
  public:
	static const int Blue = 0;
	static const int Red = 1;
	static const int Orange = 2;
	static const int Yellow = 3;
    

    static const int TOTAL = TOTAL_BUILDERS;	
	static const string names[TOTAL_BUILDERS];
	static const string symbols[TOTAL_BUILDERS];

	static int nameToId(string name);
	static int symbolToId(string symbol);
};

#endif
