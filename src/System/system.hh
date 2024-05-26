#include<iostream>
#include<deque>
#include "../Router/router.hh"

class System {
    int xDim;
    int yDim;
    unsigned int cycle;
    bool debugMode;
    // Create 2d array of routers
    Router router[4][4];

    public:
    System();
    //Functions for cycle variable
    void incrementCycleCount();
    unsigned int getCycleCount();
    //-----------------------------
    // Print function
    void print();
    //------------------------------
    //Function related to router flit
    void acceptFlit();
    void generateInjectFlit();
    void processInputPort();
    void assignOutputPort();
    void assignInputPort();
    bool isValidInjectFlit(int x, int y);
    Flit getInputFlit(int i, int j);
    void printRouterInputFlit(int x, int y);
    //---------------------------------
    //---Generate flit test------------
    void generateInjectFlit_oneRouter();
    //---------------------------------
    void printStats();
    void printCompletedFlit();
    void printValidInputFlit();
    void setDebugMode();
};

//-----------Mesh Layout------------------
// (0,0) ---- (1,0) --- (2,0) ----- (3,0)
//   |          |         |           |
//   |          |         |           |
// (0,1) ---- (1,1) --- (2,1) ----- (3,1)
//   |          |         |           |
//   |          |         |           |
// (0,2) ---- (1,2) --- (2,2) ----- (3,2)
//   |          |         |           |
//   |          |         |           |
// (0,3) ---- (1,3) --- (2,3) ----- (3,3) 