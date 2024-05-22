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
    void incrementCycleCount();
    unsigned int getCycleCount();
    void print();
};
