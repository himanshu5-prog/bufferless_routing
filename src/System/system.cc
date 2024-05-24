#include "system.hh"

System :: System(){
    cycle = 0;
    xDim = 4;
    yDim = 4;

    for (int i = 0; i < xDim; ++i){
        for (int j = 0; j < yDim; ++j){
            router[i][j].setDim(i,j);
            router[i][j].setConfig(xDim,yDim);
        }
    }
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
// Print function---------------------------------------------
void System :: print(){
    std :: cout << "This system has 16 routers in 4x4 mesh.\n";
    std :: cout << "cycle count: " << getCycleCount() << "\n";

    router[2][3].print();
}
//--------------------------------------------------------
void System:: generateInjectFlit(){

    if (cycle % 10 == 0){
        for (int i=0; i<4; ++i){
            for (int j=0; j < 4; ++j){
                if (!router[i][j].getInjectFlit().getValid()){
                    router[i][j].generateInjectFlit();
                }
            }
        }
    } else {
        for (int i=0; i<4; ++i){
            for (int j=0; j < 4; ++j){
                if (router[i][j].getInjectFlit().getValid()){
                    router[i][j].removeInjectFlit();
                }
            }
        } 
    }
}

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