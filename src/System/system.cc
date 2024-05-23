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

void System :: incrementCycleCount(){
    cycle += (unsigned int)1;
}

unsigned int System :: getCycleCount(){
    return cycle;
}

void System :: print(){
    std :: cout << "This system has 16 routers in 4x4 mesh.\n";
    std :: cout << "cycle count: " << getCycleCount() << "\n";

    router[2][3].print();
}

void System:: generateInjectFlit(){

    if (cycle % 10 == 0){
        for (int i=0; i<4; ++i){
            for (int j=0; j < 4; ++j){
                router[i][j].generateInjectFlit();
                //Print valid inject flit
                if (router[i][j].getInjectFlit().getValid())
                    router[i][j].getInjectFlit().print();
            }
        }
    } else {
        for (int i=0; i<4; ++i){
            for (int j=0; j < 4; ++j){
                router[i][j].removeInjectFlit(); 
            }
        } 
    }
}