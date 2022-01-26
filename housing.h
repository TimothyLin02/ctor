#ifndef _HOUSING_H_
#define _HOUSING_H_
#include <iostream>
#include <string>
using std::string;

class Vertice;
class Builder;

class Housing {
    int type;
    Builder *builder;
    int verticeNum;
  public:
	Housing(int type, Builder *builder, int verticeNum);
    
    // Returns the level of the Housing.
    int getType();
    // Set the level of the Housing.
    void setType(int type);

    // Returns the vertice number the instance is located on.
    int getVerticeNum();

    // Returns the builder of the housing.
    Builder *getBuilder();

    // Returns the name of the type of housing.
    string getName();
    
    // Display the housing.
    string display();
};

#endif
