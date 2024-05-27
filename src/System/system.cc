#include "system.hh"

System :: System(){
    cycle = 0;
    xDim = 4;
    yDim = 4;

    for (int i = 0; i < xDim; ++i){
        for (int j = 0; j < yDim; ++j){
            router[i][j].setDim(i,j);
            router[i][j].setConfig(xDim,yDim);
            router[i][j].isCornerEdgeRouter();
        }
    }

    stat.completedFlitCount = 0;
    stat.injectFlitCount = 0;
}

//Function related to cycle count------------
void System :: incrementCycleCount(){
    cycle += (unsigned int)1;

    for(int i = 0; i < xDim; ++i){
        for (int j = 0; j < yDim; ++j){
            router[i][j].incrementCycleCount();
        }
    }
}

unsigned int System :: getCycleCount(){
    return cycle;
}
//------------------------------------------

void System :: setDebugMode(){
    debugMode = true;

    for (int i = 0; i < xDim; ++i){
        for ( int j = 0; j < yDim; ++j){
            router[i][j].setDebugMode();
        }
    }
}

void System :: setMaxCycleCount(unsigned int x){
    maxCycleCount = x;

}

unsigned int System :: getMaxCycleCount(){
    return maxCycleCount;
}
// Print function---------------------------------------------
void System :: print(){
    std :: cout << "This system has 16 routers in 4x4 mesh.\n";
    std :: cout << "cycle count: " << getCycleCount() << "\n";

    router[2][3].print();
}
//--------------------------------------------------------
// Each router generates flit every 10 cycles.
void System:: generateInjectFlit(){

    if (cycle % 10 == 0){
        for (int i=0; i<xDim; ++i){
            for (int j=0; j < yDim; ++j){
                if (!router[i][j].getInjectFlit().getValid()){
                    router[i][j].generateInjectFlit();
                }
            }
        }
    } else {
        for (int i=0; i < xDim; ++i){
            for (int j=0; j < yDim; ++j){
                if (router[i][j].getInjectFlit().getValid()){
                    router[i][j].removeInjectFlit();
                }
            }
        } 
    }
}

// All routers will be checked if incoming flit can be accepted
void System :: acceptFlit(){
    for (int i = 0; i < xDim; ++i){
        for (int j = 0; j < yDim; ++j){
            router[i][j].acceptFlit();
        }
    }
}
//-----------------------------------------------------------
// All routers will be assigning output port to incoming flits
void System :: assignOutputPort(){
    for (int i = 0; i < xDim; ++i){
        for (int j = 0; j < yDim; ++j){
            router[i][j].routeOldestFlit();
            router[i][j].routeOtherFlit();
        }
    }
}
//-----------------------------------------------------------
//Connecting router in mesh topology--------------------------------------------------------------
void System :: assignInputPort(){

    for (int i = 0; i < xDim - 1; ++i){
        for (int j = 0; j < yDim - 1; ++j){
            
            // Connection in East-West direction
            router[i+1][j].setInputFlit(West, router[i][j].getOutputFlit(East));
            router[i][j].resetOutputFlit(East);

            if (debugMode && cycle == 0){
                std :: cout << "East --> West connection for Router : (" << i << "," << j << ") --> Router: (" << i+1 << "," << j <<")\n";
            }
            
            router[i][j].setInputFlit(East, router[i+1][j].getOutputFlit(West));
            router[i+1][j].resetOutputFlit(West);

             if (debugMode && cycle == 0){
                std :: cout << "West --> East connection for Router : (" << i+1 << "," << j << ") --> Router: (" << i << "," << j <<")\n";
            }

            // Connection in North-South direction
            router[i][j].setInputFlit(South, router[i][j+1].getOutputFlit(North));
            router[i][j+1].resetOutputFlit(North);

            if (debugMode && cycle == 0){
                std :: cout << " North  --> South connection for Router: (" << i << "," << j+1 << ") --> Router: (" << i << "," << j <<")\n";
            }

            router[i][j+1].setInputFlit(North, router[i][j].getOutputFlit(South));
            router[i][j].resetOutputFlit(South);

            if (debugMode && cycle == 0){
                std :: cout << "South --> North connection for Router: (" << i << "," << j << ") --> Router: (" << i << "," << j+1 << ")\n"; 
            }



        }
    }

    // Making missing links

    for (int i = 0; i < xDim -1; ++i){
        int  j = yDim-1;

        // Connection in East-West direction
        router[i+1][j].setInputFlit(West, router[i][j].getOutputFlit(East));
        router[i][j].resetOutputFlit(East);

        if (debugMode && cycle == 0){
            std :: cout << "East --> West connection for Router : (" << i << "," << j << ") --> Router: (" << i+1 << "," << j <<")\n";
        }

        router[i][j].setInputFlit(East, router[i+1][j].getOutputFlit(West));
        router[i+1][j].resetOutputFlit(West);

        if (debugMode && cycle == 0){
            std :: cout << "West --> East connection for Router : (" << i+1 << "," << j << ") --> Router: (" << i << "," << j <<")\n";
        }
    }

    for (int j = 0; j < yDim -1; ++j){
        int i = xDim - 1;

        // Connection in North-South direction
        router[i][j].setInputFlit(South, router[i][j+1].getOutputFlit(North));
        router[i][j+1].resetOutputFlit(North);

        if (debugMode && cycle == 0){
            std :: cout << " North  --> South connection for Router: (" << i << "," << j+1 << ") --> Router: (" << i << "," << j <<")\n";
        }

        router[i][j+1].setInputFlit(North, router[i][j].getOutputFlit(South));
        router[i][j].resetOutputFlit(South);

        if (debugMode && cycle == 0){
            std :: cout << "South --> North connection for Router: (" << i << "," << j << ") --> Router: (" << i << "," << j+1 << ")\n"; 
        }

    }
}
//---------------------------------------------------------------------------
//This function checks if injected flit can be considered for port arbitration
void System :: processInputPort(){

    for (int i = 0; i < xDim; ++i){
        for (int j = 0; j < yDim; ++j){
            router[i][j].processInputPort();
        }
    }

}
//------------------------------------------------------------------------
bool System :: isValidInjectFlit(int x, int y){

    if (router[x][y].getInjectFlit().getValid()){
        return true;
    }
    return false;
}

Flit System :: getInputFlit(int x, int y){

    return router[x][y].getInjectFlit();
}

void System :: printRouterInputFlit(int x, int y){
    std::cout << "Input Flit in router (" << x << "," << y << ")\n";
    router[x][y].getInjectFlit().print();
}

void System :: printStats(){
    std:: cout << "\nStats at cycle count: " << cycle << "\n";
    for (int i = 0; i < xDim; ++i){
        for (int j = 0; j < yDim; ++j){
            router[i][j].printStats();
        }
    }
}
 void System :: getSystemStatUpdate(){

    for (int i = 0; i < xDim; ++i){
        for (int j = 0; j < yDim; ++j){
            stat.completedFlitCount += router[i][j].stat.completedFlitCount;
            stat.injectFlitCount    += router[i][j].stat.injectFlitCount;
        }
    }
 }
 //---------------------------------------------------
// Test generation. Router[0][0] generates flit every 10 cycles.
void System :: generateInjectFlit_oneRouter(){

    if (cycle % 10 == 0){

        if (router[0][0].getInjectFlit().getValid() == false){
            router[0][0].generateInjectFlit();
        }
    } 
}
//--------------------------------------------------------------
//Print completed flit----------------------------------------
void System :: printCompletedFlit(){

    std::deque<Flit> comFl;
    
    for (int i = 0; i < xDim; ++i){
        for (int j = 0; j < yDim; ++j){
            router[i][j].printCompletedFlit();
        }
    }
}
//----------------------------------------------------------
void System :: printValidInputFlit(){
    for ( int i =0; i < xDim; ++i){
        for ( int j = 0; j < yDim; ++j){
            router[i][j].printValidInputFlit();
        }
    }
}

void System :: printRouterForbiddenList(){
    if (debugMode && cycle == 0){
        for (int i = 0; i < xDim; ++i){
            for (int j = 0; j < yDim; ++j){
                std :: cout << "Forbidden list for router ( " << i << "," << j << ")\n";
                router[i][j].printForbiddenList();
            }
        }
    }
}

void System :: printHistory(){

    for (int i = 0; i < xDim; ++i){
        for (int j = 0; j < yDim; ++j){
            router[i][j].printHistory();
        }
    }
}