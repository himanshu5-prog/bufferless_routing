#include <iostream>
#include "../src/Flit/flit.hh"
#include "../src/Router/router.hh"
#include "../src/System/system.hh"

int main(){
    System s;
    unsigned int cycleCount;
    int xDim;
    int yDim;
    unsigned int maxCycleCount = 80;

    unsigned int currentCycle;
    xDim = 4;
    yDim = 4;
    for (unsigned int currentCycle = 0; currentCycle < maxCycleCount; ++currentCycle){
       //Check if any incoming flit reached its destination----------
       s.acceptFlit();
       //------------------------------------------------------------
       //Check if core can generate the flit-------------------------
       s.generateInjectFlit();
       //------------------------------------------------------------
       //Check if the injected flit can be considered for arbitration
       s.processInputPort();
       //-------------------------------------------------------------
       //Assign output port to the incoming flit----------------------
       s.assignOutputPort();
       //-------------------------------------------------------------
       //Update input ports-------------------------------------------
       s.assignInputPort();
       //--------------------------------------------------------------
       s.incrementCycleCount();
       s.printStats();
    }
    return 0;
}