#include "router.hh"

Router :: Router (){
    xDim = 0;
    yDim = 0;
    sentFlitCount = 0;
    id = 0;
    cycle = 0;
    edgeRouter = true;
    cornerRouter = true;
    config.x = 0;
    config.y = 0;
}

Router :: Router (int x,  int y){
    xDim = x;
    yDim = y;
    sentFlitCount = 0;
    id = 0;
    cycle = 0;
    config.x = 0;
    config.y = 0;

    if (xDim == yDim){
        cornerRouter = true;
    } else {
        cornerRouter = false;
    }
    cornerRouter = false;
}

void Router :: print (){
    std :: cout << "Router information\n";
    std :: cout << "x coord: " << xDim << ", y coord: " << yDim << "\n";

    std :: cout << "Input flit in East direction:\n";
    inputFlit[East].print();

    std :: cout << "Input flit in West direction:\n";
    inputFlit[West].print();

    std :: cout << "Input flit in North direction:\n";
    inputFlit[North].print();

    std :: cout << "Input flit in South direction:\n";
    inputFlit[South].print();

}

void Router :: setInputFlit (Direction dir, Flit f){
    inputFlit[dir] = f;
}

Flit Router :: getInputFlit (Direction dir){
    return inputFlit[dir];
}

void Router :: removeInputFlit (Direction dir){
    inputFlit[dir].resetValid();
}

void Router :: setOutputFlit( Direction dir, Flit f){
    outputFlit[dir] = f;
}

Flit Router :: getOutputFlit (Direction dir){
    return outputFlit[dir];
}

void Router :: setDim (int x, int y){
    xDim = x;
    yDim = y;
}

void Router :: generateInjectFlit(){
    Flit fl;
    int xDest, yDest;
    Coord cSrc, cDest;

   
    xDest = rand()%4;
    yDest = rand()%4;

    cDest.x = xDest;
    cDest.y = yDest;

    cSrc.x = xDim;
    cSrc.y = yDim;

    fl.setValid();
    fl.setDest(cDest);
    fl.setSrc(cSrc);
    fl.setId(id);

    id += 1;

    coreInjectFlit = fl;
    
}

void Router :: setConfig(int x, int y){
    config.x = x;
    config.y = y;
}

bool Router :: canInjectFlit(){

    for (int i=0; i< TotalDir; ++i){
        if (!inputFlit[i].getValid()){
            //Empty flit
            return true;
        }
    }
    // All flits are occupied
    return false;
}

