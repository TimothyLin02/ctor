#include "builder.h"
#include "builderId.h"
#include "housing.h"
#include "housingType.h"
#include "vertice.h"
using std::string;

Housing::Housing(int type, Builder *builder, int verticeNum) :
    type{type},
    builder{builder},
    verticeNum{verticeNum}
{}

int Housing::getType() {
    return type;
}

Builder *Housing::getBuilder() {
    return builder;
}

void Housing::setType(int type) {
    if (type >= 1 && type <= 3) {
        this->type = type;
    }
}

string Housing::getName() {
    return HousingType::names[type];
}

string Housing::display() {
    return BuilderId::symbols[builder->getId()] + HousingType::names[type];
}

int Housing::getVerticeNum() {
    return verticeNum;
}

