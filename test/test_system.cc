#include <iostream>
#include "../src/Flit/flit.hh"
#include "../src/Router/router.hh"
#include "../src/System/system.hh"

int main(){
    System sys;
    unsigned int maxCycleCount = 80;

    unsigned int currentCycle;

    //TODO: Test #1: Create a test in which one router is injecting flit and see how routing is happening.
    //TODO: Test #2: Two routers are injecting traffic
    for (unsigned int currentCycle = 0; currentCycle < maxCycleCount; ++currentCycle){
       //Check if any incoming flit reached its destination----------
       sys.acceptFlit();
       //------------------------------------------------------------
       //Check if core can generate the flit-------------------------
       sys.generateInjectFlit_oneRouter();
       //sys.generateInjectFlit();
       //------------------------------------------------------------
       //Check if the injected flit can be considered for arbitration
       sys.processInputPort();
       //-------------------------------------------------------------
       //Assign output port to the incoming flit----------------------
       sys.assignOutputPort();
       //-------------------------------------------------------------
       //Update input ports-------------------------------------------
       sys.assignInputPort();
       //--------------------------------------------------------------
       sys.incrementCycleCount();
      
    }
    sys.printStats();
    sys.printCompletedFlit();
    return 0;
}