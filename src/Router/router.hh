#ifndef _ROUTER_
#define _ROUTER_

#include <iostream>
#include<deque>
#include <cstdlib>
#include "../Flit/flit.hh"
class Router {
    int xDim;
    int yDim;

    int sentFlitCount;
    unsigned int id;
    unsigned int cycle;
    Flit inputFlit[TotalDir];
    Flit outputFlit[TotalDir];
    Flit coreInjectFlit;

    std::deque<Flit> coreCompletedFlit;

    public:

    Router();
    Router(int x, int y);
    void setDim(int x, int y);
    void print();
    void setInputFlit(Direction dir, Flit f);
    Flit getInputFlit(Direction dir);
    void removeInputFlit (Direction dir);

    // Create function to set/get flit from output (flit) buffer
    void setOutputFlit (Direction dir, Flit f);
    Flit getOutputFlit (Direction dir);
    void generateInjectFlit();
    void incrementCycleCount() {cycle += 1;}

    
    
};

#endif
