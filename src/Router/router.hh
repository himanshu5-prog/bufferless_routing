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

//Stats for Router------------------------------------------------------------------------------
struct Stats{
    unsigned int injectFlitCount; // Number of flits injected by router
    unsigned int completedFlitCount; // Number of flits that was absorbed by destination router 
};
//----------------------------------------------------------------------------------------------

//This enum contains information regarding port type of router 
// that a flit entered. When a flit gets generated, it is set to 'Source'.
enum PortType {
    Input,
    Output,
    Destination,
    Source,
    totalPortDir

};
//------------------------------------------------------------------------------------------
//Whenever oldest input flit is selected to route, it is guaranteed to route in optimized way.
// Rest of input flit are not guruanteed to be routed in this way.
enum RoutingType{
    Optimized,
    NonOptimized,
    NA
};
//-------------------------------------------------------------------------------------------
// Every router stores history data structure containing information of flit generated, entered
// or extited the router. This help in tracking each flit and facilitates debugging
struct History {
    int xSrc;
    int ySrc;
    int xDest;
    int yDest;
    int id;
    int time;
    RoutingType routingType;
    PortType portType;
    Direction dir;
};
//--------------------------------------------------------------------------------------------
//Functions to convert enum to string for printing purpose
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

inline std :: string convertRoutingType2String( RoutingType r){
    if (r == Optimized){
        return "Optimized";
    }

    if ( r == NonOptimized){
        return "NonOptimized";
    }
    
    if ( r == NA){
        return "NA";
    }

    return "Unknown";
}
//------------------------------------------------------------------------------------------

class Router {
    int xDim;
    int yDim;
    Coord config;
    int cornerEdge;
    int sentFlitCount;
    unsigned int id;
    unsigned int cycle;
    //Input port buffer----------
    Flit inputFlit[TotalDir];
    //----------------------
    //Output port buffer-----------
    Flit outputFlit[TotalDir];
    //------------------------
    //Injected flit-----------
    Flit coreInjectFlit;
    //------------------------
    //List of flits absorbed by destination flit
    std::deque<Flit> coreCompletedFlit;
    //-----------------------------------------
    bool debugMode;
    //List of forbidden input & output buffer
    std :: set <int> forbiddenPort;
    //--------------------------------------
    //Router history data structure----------
    std :: vector <History> history;
    //---------------------------------------

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

    void isCornerEdgeRouter(); // Check if router is in corner or edge and create forbidden port list accordingly
    bool IsForbiddenPort (int i);
    void printForbiddenList();
    void printHistory();
};

#endif
