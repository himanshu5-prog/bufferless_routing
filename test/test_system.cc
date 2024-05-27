#include <iostream>
#include "../src/Flit/flit.hh"
#include "../src/Router/router.hh"
#include "../src/System/system.hh"

int main (int argc, char* argv[]){
    std :: cout << "Total number of arguments: " << argc << "\n";
    unsigned int maxCycleCount = 16;
    bool debugMode = false;
    int i=1;

 
    while (i < argc){
        if (!strcmp(argv[i], "--debugMode")){
            unsigned long ul = std :: stoul(argv[i+1]);
            std :: cout << argv[i] << " is being used.\n";
            debugMode = static_cast<bool> (ul);
            i += 2;

        } else if ( !strcmp(argv[i], "--maxCycleCount")){
            unsigned long ul = std :: stoul(argv[i+1]);
            std :: cout << argv[i] << " is being used.\n";
            maxCycleCount = static_cast<unsigned int> (ul);
            i += 2;

        } else if ( !strcmp(argv[i], "--help")){
            std :: cout << "--help is used. There are two valid command-line arguments\n --> --debugMode: Default is false\n";
            std :: cout << "--> --maxCycleCount: Default is 16.\n";
            return 1;
        } else {
            std :: cout << "Invalid commandline : " << argv[i] << "used. Use --help to see list of valid arguments\n";
            return 2;
        }
    }
    std :: cout << "debugMode set to " << debugMode << "\n";
    std :: cout << "maxCycleCount set to " << maxCycleCount << "\n";


    // System test
    System sys;
    
    unsigned int currentCycle;
    sys.setMaxCycleCount(maxCycleCount);
   //sys.setDebugMode();
    sys.printRouterForbiddenList();
    for (unsigned int currentCycle = 0; currentCycle < sys.getMaxCycleCount(); ++currentCycle){
       //Check if any incoming flit reached its destination----------
       sys.acceptFlit();
       //------------------------------------------------------------
       //Check if core can generate the flit-------------------------
       //sys.generateInjectFlit_oneRouter();
       sys.generateInjectFlit(); 
       //------------------------------------------------------------
       //Check if the injected flit can be considered for arbitration
       sys.processInputPort();
       //-------------------------------------------------------------
       if (debugMode){
        sys.printValidInputFlit();
       }
       //Assign output port to the incoming flit----------------------
       sys.assignOutputPort();
       //-------------------------------------------------------------
       //Update input ports-------------------------------------------
       sys.assignInputPort();
       //--------------------------------------------------------------
       sys.incrementCycleCount();
      
    }

    if (debugMode){
        sys.printStats();
        sys.printCompletedFlit();
    }
    sys.printHistory();
    sys.getSystemStatUpdate();

    std :: cout << "System injected flit: " << sys.stat.injectFlitCount << "\nSystem completed flit: " << sys.stat.completedFlitCount << "\n";
    return 0;

}