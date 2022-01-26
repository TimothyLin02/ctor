#ifndef BUILDER_H
#define BUILDER_H
#include <string>
#include <vector>
using std::string;
using std::vector;

class Housing;
class Road;
class Dice;

class Builder {
    int id;
    Dice *dice;
    vector<Housing *> housings;
    vector<Road *> roads;
    vector<int> numResources;
  public:
    Builder(int id, Dice *dice);
    
    ~Builder();

    // Returns the id of the instance of builder
    int getId();
    
    // Set the type of dice the builder is using
    void setDice(Dice *dice);
    // Get the dice the builder is using
    Dice *getDice();

    // Returns a list of housing that the builder owns
    vector<Housing *> &getHousings();
    // Returns a list of roads that the builder owns
    vector<Road *> &getRoads();

    // Returns a list of amount of each resource that the builder has
    vector<int> &getNumResources();

    // Returns the total number of resources the builder has
    int totalResources();
    
    // add amount of resources to the builder
    void addResources(int type, int amount);

    // subtracts amount of resources from the builder
    void subResources(int type, int amount);

    // Returns the colour of the builder
    string getName();
    // Returns the first letter of the colour of the builder
    string getSymbol();

    // Adds a new road to the builder
    void addRoad(Road *newRoad);
    // Adds a new housing to the builder
    void addHousing(Housing *newRes);

    // Returns the number of points the builder has
    int getBuildingPoints();
};

#endif
