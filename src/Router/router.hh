#ifndef _ROUTER_
#define _ROUTER_

#include <iostream>
#include<deque>
#include <cstdlib>
#include <cassert>
#include <set>
#include <vector>
#include <map>
#include "../Flit/flit.hh"

struct Stats{
    unsigned int injectFlitCount;
    unsigned int completedFlitCount;
};


enum PortType {
    Input,
    Output,
    Destination,
    Source,
    totalPortDir

};

struct History {
    int xSrc;
    int ySrc;
    int xDest;
    int yDest;
    int id;
    int time;
    PortType portType;
    Direction dir;
};

inline std :: string convertPortType2String(PortType p){
    if (p == Input){
        return "Input";
    }

    if (p == Output){
        return "Output";
    }

    if (p == Destination){
        return "Destination";
    }

    if (p == Source){
        return "Source";
    }

    return "Unknown";
}
class Router {
    int xDim;
    int yDim;
    Coord config;
    int cornerEdge;
    int sentFlitCount;
    unsigned int id;
    unsigned int cycle;
    Flit inputFlit[TotalDir];
    Flit outputFlit[TotalDir];
    Flit coreInjectFlit;
    std::deque<Flit> coreCompletedFlit;
    bool debugMode;
    std :: set <int> forbiddenPort;
    std :: vector <History> history;

    public:
    
    //Constructor--------
    Router();
    Router(int x, int y);
    //-------------------
    //Misc. Function------------------------
    void setConfig(int x, int y);
    void setDim(int x, int y);
    void incrementCycleCount() {cycle += 1;}
    void setCycleCount(unsigned int c) { cycle = c;}
    unsigned int getCycleCount() { return cycle;}
    //---------------------------------------
    //Print functions----------------------
    void print();
    ///-----------------------------------
    // Functions for InputFlit--------------
    void setInputFlit(Direction dir, Flit f);
    Flit getInputFlit(Direction dir);
    void removeInputFlit (Direction dir);
    void printValidInputFlit();
    //--------------------------------------
    // Functions for outputFlit-----------------
    void setOutputFlit (Direction dir, Flit f);
    Flit getOutputFlit (Direction dir);
    void removeOutputFlit(Direction dir);
    //------------------------------------------
    // Function for inject flit-------------
    void generateInjectFlit();
    Flit getInjectFlit();
    void removeInjectFlit();
    bool canInjectFlit(); // Determine if there inject flit can be sent out of router
    void insertInjectFlit();
    //------------------------------------------------------------    
    //Functions related to routing
    Direction getOutputPortDirection(int xDest, int yDest, int id);
    void processInputPort(); // Create final list of input flit
    Direction getOldestInputFlit();
    void resetInputFlit(Direction dir) { inputFlit[dir].resetValid(); }
    void resetOutputFlit(Direction dir) {outputFlit[dir].resetValid();}
    int validInputFlitCount();
    void acceptFlit();
    void routeOldestFlit();
    void routeOtherFlit();
    void routeFlit();
    //-----------------------------------------------
    Stats stat;
    void printStats();
    std::deque<Flit> getCompletedFlitList() { return coreCompletedFlit;}
    void printCompletedFlit();

    void setDebugMode();

    void isCornerEdgeRouter();
    bool IsForbiddenPort (int i);
    void printForbiddenList();
    void printHistory();
};

#endif
