#include <iostream>
#include <string>
#include <stdio.h>
#include "board.h"
#include "builder.h"
#include "edge.h"
#include "housing.h"
#include "road.h"
#include "resourceType.h"
#include "tile.h"
#include "view.h"
#include "vertice.h"
using std::cout;
using std::endl;

View::View() {}

View *View::getInstance() {
    static View view;
    return &view;
}

void View::printBoard(Board *board) {
    int v = 0, e = 0, t = 0;    
    // line 1
    printf("                    |%2s|--%2s--|%2s|\n", 
        board->getVertices()[v]->display().c_str(), 
        board->getEdges()[e]->display().c_str(),
        board->getVertices()[v + 1]->display().c_str());
        
    // line 2
    printf("                      |         |\n");

    // line 3
    printf("                     %2s   %2d   %2s\n", 
        board->getEdges()[e + 1]->display().c_str(),
        board->getTiles()[t]->getNumber(),
        board->getEdges()[e + 2]->display().c_str());
        
    // line 4
    printf("                      |  %-7s|\n",
        board->getTiles()[t]->strType().c_str());
        
    // line 5
    printf("          |%2s|--%2s--|%2s|  %2s  |%2s|--%2s--|%2s|\n", 
        board->getVertices()[v + 2]->display().c_str(), 
        board->getEdges()[e + 3]->display().c_str(),
        board->getVertices()[v + 3]->display().c_str(), 
        board->getTiles()[t]->strValue().c_str(), 
        board->getVertices()[v + 4]->display().c_str(), 
        board->getEdges()[e + 4]->display().c_str(),
        board->getVertices()[v + 5]->display().c_str());
        
    // line 6
    printf("            |         |  %5s  |         |\n", 
        board->getTiles()[t]->strGeese().c_str());
        
    // line 7
    printf("           %2s   %2d   %2s        %2s   %2d   %2s\n", 
        board->getEdges()[e + 5]->display().c_str(), 
        board->getTiles()[t + 1]->getNumber(),
        board->getEdges()[e + 6]->display().c_str(), 
        board->getEdges()[e + 7]->display().c_str(), 
        board->getTiles()[t + 2]->getNumber(), 
        board->getEdges()[e + 8]->display().c_str());
        
    // line 8
    printf("            |  %-7s|         |  %-7s|\n", 
        board->getTiles()[t + 1]->strType().c_str(), 
        board->getTiles()[t + 2]->strType().c_str());

    v = 6;
    e = 9;
    t = 1;
    for (int i = 0; i < 3; i++) {
        // line 9, 17, 25 
        printf("|%2s|--%2s--|%2s|  %2s  |%2s|--%2s--|%2s|  %2s  |%2s|--%2s--|%2s|\n", 
            board->getVertices()[v]->display().c_str(),
            board->getEdges()[e]->display().c_str(), 
            board->getVertices()[v + 1]->display().c_str(), 
            board->getTiles()[t]->strValue().c_str(), 
            board->getVertices()[v + 2]->display().c_str(),
            board->getEdges()[e + 1]->display().c_str(), 
            board->getVertices()[v + 3]->display().c_str(), 
            board->getTiles()[t + 1]->strValue().c_str(), 
            board->getVertices()[v + 4]->display().c_str(),
            board->getEdges()[e + 2]->display().c_str(), 
            board->getVertices()[v + 5]->display().c_str());
            
        // line 10, 18, 26
        printf("  |         |  %5s  |         |  %5s  |         |\n",
            board->getTiles()[t]->strGeese().c_str(),
            board->getTiles()[t+1]->strGeese().c_str());

        e += 3;
        t += 2;
            
        // line 11, 19, 27
        printf(" %2s   %2d   %2s        %2s   %2d   %2s        %2s   %2d   %2s\n", 
            board->getEdges()[e]->display().c_str(),
            board->getTiles()[t]->getNumber(), 
            board->getEdges()[e + 1]->display().c_str(), 
            board->getEdges()[e + 2]->display().c_str(), 
            board->getTiles()[t + 1]->getNumber(), 
            board->getEdges()[e + 3]->display().c_str(),
            board->getEdges()[e + 4]->display().c_str(), 
            board->getTiles()[t + 2]->getNumber(), 
            board->getEdges()[e + 5]->display().c_str());
            
        // line 12, 20, 28
        printf("  |  %-7s|         |  %-7s|         |  %-7s|\n", 
            board->getTiles()[t]->strType().c_str(), 
            board->getTiles()[t + 1]->strType().c_str(),
            board->getTiles()[t + 2]->strType().c_str());

        v += 6;
        e += 6;
            
        // line 13, 21, 29
        printf("|%2s|  %2s  |%2s|--%2s--|%2s|  %2s  |%2s|--%2s--|%2s|  %2s  |%2s|\n", 
            board->getVertices()[v]->display().c_str(),
            board->getTiles()[t]->strValue().c_str(), 
            board->getVertices()[v + 1]->display().c_str(), 
            board->getEdges()[e]->display().c_str(), 
            board->getVertices()[v + 2]->display().c_str(),
            board->getTiles()[t + 1]->strValue().c_str(), 
            board->getVertices()[v + 3]->display().c_str(), 
            board->getEdges()[e + 1]->display().c_str(), 
            board->getVertices()[v + 4]->display().c_str(),
            board->getTiles()[t + 2]->strValue().c_str(), 
            board->getVertices()[v + 5]->display().c_str());
           
        // line 14, 22, 30
        printf("  |  %5s  |         |  %5s  |         |  %5s  |\n",
            board->getTiles()[t]->strGeese().c_str(),
            board->getTiles()[t+1]->strGeese().c_str(),
            board->getTiles()[t+2]->strGeese().c_str());

        e += 2;
        t += 3;
            
        // line 15, 23, 31
        printf(" %2s        %2s   %2d   %2s        %2s   %2d   %2s        %2s\n", 
            board->getEdges()[e]->display().c_str(),
            board->getEdges()[e + 1]->display().c_str(), 
            board->getTiles()[t]->getNumber(), 
            board->getEdges()[e + 2]->display().c_str(), 
            board->getEdges()[e + 3]->display().c_str(), 
            board->getTiles()[t + 1]->getNumber(),
            board->getEdges()[e + 4]->display().c_str(), 
            board->getEdges()[e + 5]->display().c_str());
          
        // line 16, 24, 32
        printf("  |         |  %-7s|         |  %-7s|         |\n", 
            board->getTiles()[t]->strType().c_str(), 
            board->getTiles()[t + 1]->strType().c_str());

        v += 6;
        e += 6;
    }
        
    // line 33
    printf("|%2s|--%2s--|%2s|  %2s  |%2s|--%2s--|%2s|  %2s  |%2s|--%2s--|%2s|\n", 
        board->getVertices()[v]->display().c_str(),
        board->getEdges()[e]->display().c_str(), 
        board->getVertices()[v + 1]->display().c_str(), 
        board->getTiles()[t]->strValue().c_str(), 
        board->getVertices()[v + 2]->display().c_str(), 
        board->getEdges()[e + 1]->display().c_str(),
        board->getVertices()[v + 3]->display().c_str(), 
        board->getTiles()[t + 1]->strValue().c_str(), 
        board->getVertices()[v + 4]->display().c_str(), 
        board->getEdges()[e + 2]->display().c_str(),
        board->getVertices()[v + 5]->display().c_str());

    // line 34
    printf("            |  %5s  |         |  %5s  |\n",
        board->getTiles()[t]->strGeese().c_str(),
        board->getTiles()[t+1]->strGeese().c_str());

    e += 3;
    t += 2;
        
    // line 35
    printf("           %2s        %2s   %2d   %2s        %2s\n", 
        board->getEdges()[e]->display().c_str(), 
        board->getEdges()[e + 1]->display().c_str(),
        board->getTiles()[t]->getNumber(), 
        board->getEdges()[e + 2]->display().c_str(), 
        board->getEdges()[e + 3]->display().c_str());

    // line 36
    printf("            |         |  %-7s|         |\n", 
        board->getTiles()[t]->strType().c_str());

    v += 6;
    e += 4;
        
    // line 37
    printf("          |%2s|--%2s--|%2s|  %2s  |%2s|--%2s--|%2s|\n", 
        board->getVertices()[v]->display().c_str(), 
        board->getEdges()[e]->display().c_str(),
        board->getVertices()[v + 1]->display().c_str(), 
        board->getTiles()[t]->strValue().c_str(), 
        board->getVertices()[v + 2]->display().c_str(), 
        board->getEdges()[e + 1]->display().c_str(),
        board->getVertices()[v + 3]->display().c_str());
        
    // line 38
    printf("                      |  %5s  |\n",
        board->getTiles()[t]->strGeese().c_str());
        
    // line 39
    printf("                     %2s        %2s\n", 
        board->getEdges()[e + 2]->display().c_str(), 
        board->getEdges()[e + 3]->display().c_str());
        
    // line 40
    printf("                      |         |\n");
        
    // line 41
    printf("                    |%2s|--%2s--|%2s|\n", 
        board->getVertices()[v + 4]->display().c_str(), 
        board->getEdges()[e + 4]->display().c_str(),
        board->getVertices()[v + 5]->display().c_str());
}

void View::printBuilder(Builder *builder) {
    cout << builder->getName() << " has ";
    cout << builder->getBuildingPoints() << " building points, ";
    cout << builder->getNumResources()[ResourceType::BRICK] << " brick, ";
    cout << builder->getNumResources()[ResourceType::ENERGY] << " energy, ";
    cout << builder->getNumResources()[ResourceType::GLASS] << " glass, ";
    cout << builder->getNumResources()[ResourceType::HEAT] << " heat, and ";
    cout << builder->getNumResources()[ResourceType::WIFI] << " WiFi." << endl;
    if (!builder->getHousings().empty()) {
        cout << builder->getName() << " has built:" << endl;
        printResidences(builder);
    }
}

void View::printResidences(Builder *builder) {
    int size = builder->getHousings().size();
    for (int i = 0; i < size; ++i) {
        cout << builder->getHousings()[i]->getVerticeNum() << " ";
        cout << builder->getHousings()[i]->getName() << endl;
    }
}

void View::invalidInput() {
    cout << "Invalid input." << endl;
}

void View::invalidCommand() {
    cout << "Invalid command." << endl;
}

void View::cannotBuildHere() {
    cout << "You cannot build here." << endl;
}

void View::doNotHaveEnoughResources() {
    cout << "You do not have enough resources." << endl;
}



