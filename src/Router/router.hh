#ifndef _ROUTER_
#define _ROUTER_

#include <iostream>
#include<deque>
#include <cstdlib>
#include <cassert>
#include "../Flit/flit.hh"
class Router {
    int xDim;
    int yDim;
    Coord config;
    bool cornerRouter;
    bool edgeRouter;
    int sentFlitCount;
    unsigned int id;
    unsigned int cycle;
    Flit inputFlit[TotalDir];
    Flit outputFlit[TotalDir];
    Flit coreInjectFlit;

    std::deque<Flit> coreCompletedFlit;

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
    void resetOldestInputFlit(Direction dir) { inputFlit[dir].resetValid(); };
    int validInputFlitCount();
    void acceptInjectFlit();
    
};

#endif
