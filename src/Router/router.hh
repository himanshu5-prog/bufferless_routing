#ifndef _ROUTER_
#define _ROUTER_

#include <iostream>
#include<deque>
#include <cstdlib>
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
    //---------------------------------------
    //Print functions----------------------
    void print();
    ///-----------------------------------
    // Functions for InputFlit--------------
    void setInputFlit(Direction dir, Flit f);
    Flit getInputFlit(Direction dir);
    void removeInputFlit (Direction dir);
    //--------------------------------------
    // Functions for outputFlit---------------
    void setOutputFlit (Direction dir, Flit f);
    Flit getOutputFlit (Direction dir);
    void removeOutputFlit(Direction dir);
    //------------------------------------
    // Function for inject flit-------------
    void generateInjectFlit();
    Flit getInjectFlit();
    void removeInjectFlit();
    bool canInjectFlit();
    //------------------------------------------------------------    
    
};

#endif
