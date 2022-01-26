#include "builder.h"
#include "edge.h"
#include "exceptions.h"
#include "gameRule.h"
#include "housing.h"
#include "housingType.h"
#include "resourceType.h"
#include "road.h"
#include "vertice.h"
using std::vector;

GameRule::GameRule() {}

GameRule *GameRule::getInstance() {
    static GameRule gameRule;
    return &gameRule;
}

void GameRule::buildBasementFree(Builder *builder, Vertice *vertice) {
    if (vertice->getHousing() != nullptr) {
		throw AlreadyBuiltException{};
	}		
	vertice->setHousing(new Housing(HousingType::B, builder, vertice->getNumber()));
	builder->getHousings().push_back(vertice->getHousing());    
}

bool GameRule::noAdjHousing(Vertice *vertice) {
	vector<Edge *> edges = vertice->getEdges();
	for (std::size_t i = 0; i < edges.size(); i++) {
		vector<Vertice *> otherVert = edges[i]->getVertices();
		for (std::size_t j = 0; j < otherVert.size(); j++) {
			if (otherVert[j]->getHousing() != nullptr) {
				return false;
			}
		}
	}
	return true;
}

bool GameRule::ownRoad(int builder, Vertice *vertice) {
	vector<Edge *> edges = vertice->getEdges();
	for (std::size_t i = 0; i < edges.size(); i++) {
		Road *road = edges[i]->getRoad();
		if (road != nullptr) {
			if (road->getBuilderId() == builder) {
				return true;
			}
		}
	}
	return false;
}

/*
    matrix to build:
        canBuild    |    Adj  |   Road
        --------------------------------
                    |     x   |    x
        --------------------------------
           Yes      |     x   |   Yes
        --------------------------------
                    |    Yes  |    x
        --------------------------------
                    |    Yes  |   Yes
*/
void GameRule::buildBasement(Builder * builder, Vertice *vertice) {
	int id = builder->getId();
	vector<int> resources = builder->getNumResources();
	if ((resources[ResourceType::GLASS] < 1) || (resources[ResourceType::BRICK] < 1) ||
        (resources[ResourceType::ENERGY] < 1) || (resources[ResourceType::WIFI] < 1)) {
		throw NotEnoughResourceException{};
	} else if (vertice->getHousing() != nullptr) {
		throw AlreadyBuiltException{};
	} else if (noAdjHousing(vertice) == false) {
		throw AdjacentResidenceException{};
	} else if (ownRoad(id, vertice) == false) {
		throw NoRoadToVerticeException{};
    }   
         
	Housing *residence = new Housing(1, builder, vertice->getNumber());
	builder->subResources(ResourceType::GLASS, 1);
	builder->subResources(ResourceType::BRICK, 1);
	builder->subResources(ResourceType::ENERGY, 1);
	builder->subResources(ResourceType::WIFI, 1);
	vertice->setHousing(residence);
	builder->addHousing(residence);
}

void GameRule::buildHouse(Builder * builder, Vertice *vertice) {
	vector<int> resources = builder->getNumResources();
	if (resources[ResourceType::GLASS] < 2 || resources[ResourceType::HEAT] < 3) {
		throw NotEnoughResourceException{};
	}
	Housing *curHousing = vertice->getHousing();
	if ((curHousing == nullptr) || (curHousing->getBuilder() != builder)) {
       throw NotOwnedException{};
	}
	curHousing->setType(2);
	builder->subResources(ResourceType::GLASS, 2);
	builder->subResources(ResourceType::HEAT, 3);
}

void GameRule::buildTower(Builder * builder, Vertice *vertice) {
	Housing *curHousing = vertice->getHousing();
    if ((curHousing == nullptr) || (curHousing->getBuilder() != builder)) {
        throw NotOwnedException{};
    }
    vector<int> resources = builder->getNumResources();
    if ((resources[ResourceType::GLASS] >= 2) && (resources[ResourceType::BRICK] >= 3) &&
	    (resources[ResourceType::ENERGY] >= 2) && (resources[ResourceType::WIFI] >= 1) &&
	    (resources[ResourceType::HEAT] >= 2)) {
            vertice->getHousing()->setType(3);
            builder->subResources(ResourceType::GLASS, 2);
            builder->subResources(ResourceType::BRICK, 3);
            builder->subResources(ResourceType::ENERGY, 2);
            builder->subResources(ResourceType::HEAT, 2);
            builder->subResources(ResourceType::WIFI, 1);
    } else {
        throw NotEnoughResourceException{};
    }
}

bool GameRule::canBuildRoad(Builder * builder, Edge *edge) {
	vector<Vertice *> vertices = edge->getVertices();
	int id = builder->getId();
	for (std::size_t i = 0; i < vertices.size(); i++) {
        Housing *residence = vertices[i]->getHousing();
		if (residence != nullptr) {
			if (residence->getBuilder()->getId() == id) {
				return true;
			}
		}
		vector<Edge *> curEdges = vertices[i]->getEdges();
		for (std::size_t j = 0; j < curEdges.size(); j++) {
			Road *road = curEdges[j]->getRoad();
			if (road != nullptr) {
				if (road->getBuilderId() == id) {
					return true;
				}
			}
		}
	}
	return false;
}

void GameRule::buildRoad(Builder *builder, Edge *edge) {
	vector<int> resources = builder->getNumResources();
	if ((resources[ResourceType::HEAT] < 1) || (resources[ResourceType::WIFI] < 1)) {
		throw NotEnoughResourceException{};
	} else if (edge->getRoad() != nullptr) {
		throw AlreadyBuiltException{};
	} else if (canBuildRoad(builder, edge) == false) {
		throw NoConnectionToEdgeException{};
	}
	Road *road = new Road(builder->getId(), edge->getNumber());
    builder->subResources(ResourceType::HEAT, 1);
    builder->subResources(ResourceType::WIFI, 1);
    edge->setRoad(road);
    builder->addRoad(road);
}

void GameRule::trade(Builder *builder, Builder *tradeBuilder, int giveResource, int takeResource) {
    vector<int> resources = builder->getNumResources();
    vector<int> tradeResources = tradeBuilder->getNumResources();
    if ((resources[giveResource] < 1) || (tradeResources[takeResource] < 1)) {
        throw NotEnoughResourceException{};
    }
    builder->subResources(giveResource, 1);
    builder->addResources(takeResource, 1);
    tradeBuilder->subResources(takeResource, 1);
    tradeBuilder->addResources(giveResource, 1);
}


