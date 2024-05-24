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
       //generate flits in router
       s.generateInjectFlit();

        for (int i=0; i < xDim; ++i){
            for (int j=0; j < yDim; ++j){
                if (s.isValidInjectFlit(i,j)){
                    s.printRouterInputFlit(i,j);
                }
            }
        }
       s.incrementCycleCount();
    }
    return 0;
}