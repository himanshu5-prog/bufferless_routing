#include<iostream>
#include "../Router/router.hh"

class System {
    int xDim;
    int yDim;
    unsigned int cycle;
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
    void generateInjectFlit();
    bool isValidInjectFlit(int x, int y);
    Flit getInputFlit(int i, int j);
    void printRouterInputFlit(int x, int y);
    //---------------------------------
};
