#include "router.hh"

//Constructor----------------------------------------------
Router :: Router (){
    xDim = 0;
    yDim = 0;
    sentFlitCount = 0;
    id = 0;
    cycle = 0;
    
    config.x = 0;
    config.y = 0;
    stat.completedFlitCount = 0;
    stat.injectFlitCount = 0;
}

Router :: Router (int x,  int y){
    xDim = x;
    yDim = y;
    sentFlitCount = 0;
    id = 0;
    cycle = 0;
    config.x = 0;
    config.y = 0;

    isCornerEdgeRouter();
    stat.completedFlitCount = 0;
    stat.injectFlitCount = 0;
}

void Router :: setDebugMode(){
    debugMode = true;
}
//------------------------------------------------------------------
//Print function--------------------------------------------------------
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
//-----------------------------------------------------------
//Functions for inputFlit----------------------------
void Router :: setInputFlit (Direction dir, Flit f){
    inputFlit[dir] = f;
}

Flit Router :: getInputFlit (Direction dir){
    return inputFlit[dir];
}

void Router :: removeInputFlit (Direction dir){
    inputFlit[dir].resetValid();
}
//--------------------------------------------
//Functions for output Flit---------------------------
void Router :: setOutputFlit( Direction dir, Flit f){
    outputFlit[dir] = f;
}

Flit Router :: getOutputFlit (Direction dir){
    return outputFlit[dir];
}

void Router :: removeOutputFlit (Direction dir){
    outputFlit[dir].resetValid();
}
//--------------------------------------------------
//Misc Functions-----------------------------------
void Router :: setDim (int x, int y){
    xDim = x;
    yDim = y;
}

void Router :: setConfig(int x, int y){
    config.x = x;
    config.y = y;
}
//------------------------------------------------
//Function fot injectFlit----------------------------
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
    fl.setInjectTime(cycle);
    id += 1;
   
   if ( !(cDest.x == cSrc.x && cDest.y == cSrc.y) ){

        coreInjectFlit = fl;
        stat.injectFlitCount += 1;

        if (debugMode){
            std :: cout << "(generateInjectFlit):: Router (" << xDim << "," << yDim << ") Injected flit:\n";
            coreInjectFlit.print();

        }
        //-----------------------------------
        // Flit is getting injected.
        History hist;

        hist.xSrc = coreInjectFlit.getSrc().x;
        hist.ySrc = coreInjectFlit.getSrc().y;

        hist.xDest = coreInjectFlit.getDest().x;
        hist.yDest = coreInjectFlit.getDest().y;

        hist.dir = East;
        hist.id = coreInjectFlit.getId();
        hist.portType = Source;
        hist.time = getCycleCount();

        history.push_back(hist);
        //------------------------------------
   } 
    
}

bool Router :: canInjectFlit(){
    
    if (coreInjectFlit.getValid()) {
        for (int i=0; i< TotalDir; ++i){

            if (IsForbiddenPort(i)){
                //The port cannot be used.
                continue;
            }

            if (!inputFlit[i].getValid()){
                //Empty flit
                return true;
            }
        }
    }
    // All flits are occupied
    return false;
}

Flit Router :: getInjectFlit(){
    return coreInjectFlit;
}

void Router :: removeInjectFlit(){
    coreInjectFlit.resetValid();

}

void Router :: insertInjectFlit(){
    assert (coreInjectFlit.getValid());

    for (int i=0; i< TotalDir; ++i){

        if (IsForbiddenPort(i)){
            continue;
        }
        if (!inputFlit[i].getValid()){
               inputFlit[i] = coreInjectFlit;
               //--------------------------------
               // inject flit is getting assigned to input port
               /*
               History hist;

               hist.xSrc = coreInjectFlit.getSrc().x;
               hist.ySrc = coreInjectFlit.getSrc().y;

               hist.xDest = coreInjectFlit.getDest().x;
               hist.yDest = coreInjectFlit.getDest().y;

               hist.dir = (Direction)i;
               hist.id = coreInjectFlit.getId();
               hist.portType = Input;
               hist.time = getCycleCount();

               history.push_back(hist);
               */
               //----------------------------------------

               coreInjectFlit.resetValid();
               return;
        }
    }
}

void Router :: printValidInputFlit(){
    
    if (validInputFlitCount() == 0){
        return;
    }

    std::cout << "\n Input flit for Router (" << xDim << "," << yDim << ") in cycle: " << cycle << "\n";
    for (int i = 0; i < TotalDir; ++i){
        if (inputFlit[i].getValid()){
            inputFlit[i].print();
            std :: cout << "Direction: " << convert2Direction( (Direction)i) << "\n";
        }
    }
    std :: cout << "-------------------------------------------------------\n";
}
//----------------------------------------------------
//Functions related to Routing
Direction Router :: getOutputPortDirection(int xDest, int yDest, int id){

    if (xDest == xDim){
        //assert (yDest != yDim);
        if (yDest > yDim){
            return South;

        } else if ( yDest < yDim){
            return North;
        }

    } else if ( yDest == yDim){
        //assert(xDest != xDim);

        if (xDest > xDim){
            return East;

        } else if ( xDest < xDim){
            return West;
        }
    } else if ( (xDest > xDim) && (yDest > yDim) ){
        return (id % 2) ? East : South;

    } else if ((xDest > xDim) && (yDest < yDim) ){
        return  (id % 2)? East: North;

    } else if ((xDest < xDim) && (yDest > yDim)){
        return (id %2 ) ? West : South;

    } else if ( xDest < xDim && (yDest < yDim)){
        return (id % 2) ? West : North;
    } 

    return East;
}

void Router :: processInputPort(){
    //Check if inject flit can be routed. 
    // Inject flit can be inseted to input flit only when
    // -> inject flit is valid. AND
    // -> there is free space in input flit buffer 
    if (canInjectFlit()){
        insertInjectFlit();
    }

    for (int i = 0; i < TotalDir; ++i){
        if (inputFlit[i].getValid()){
        //---------------------------------
        // Checking every input port
        History hist;
        hist.xSrc = inputFlit[i].getSrc().x;
        hist.ySrc = inputFlit[i].getSrc().y;
        hist.xDest = inputFlit[i].getDest().x;
        hist.yDest = inputFlit[i].getDest().y;

        hist.id = inputFlit[i].getId();
        hist.portType = Input;
        hist.dir = Direction(i);
        hist.time = getCycleCount();

        history.push_back(hist);
        //---------------------------------
        }
    }
}

// determine how many input flits are valid
int Router :: validInputFlitCount(){
    int x  = 0;
    for (int i = 0; i < TotalDir; ++i){

        if (IsForbiddenPort(i)){
            assert(inputFlit[i].getValid() == false);
            continue;
        }

        if (inputFlit[i].getValid()){
         
            x += 1;
        }
    }

    return x;
}

//Gives us oldest flit on input side
Direction Router :: getOldestInputFlit(){
    
    int t;
    bool found = false;
    Direction dir = East;
    for (int i = 0; i < TotalDir; ++i){

        if (IsForbiddenPort(i)){
            assert (inputFlit[i].getValid() == false);
            continue;
        }

        if (inputFlit[i].getValid() == false){
            continue;
        }

        if (found == false){
            t = inputFlit[i].getInjectTime();
            found = true;
            dir = (Direction)i;
        } else {
            if ( t > inputFlit[i].getInjectTime()){
                t = inputFlit[i].getInjectTime();
                dir = (Direction)i;
            }
        }
    }
    return dir;  
}

// Determine if either of input flit can be accepted
void Router :: acceptFlit(){

    for(int i = 0; i < TotalDir; ++i){

        if (IsForbiddenPort(i)){
            
            if (inputFlit[i].getValid()){
                std :: cout << "Port: " << i << " is forbidden in router ( " << xDim << "," << yDim << ")\n";

                std :: set <int> :: iterator itr;
                std :: cout << "Size of forbidden port: " << forbiddenPort.size() << "\n";

                if (forbiddenPort.size() > 0) {
                    for (itr = forbiddenPort.begin(); itr != forbiddenPort.end(); ++itr){
                        std :: cout << *itr << "\n";
                    }
                }
            }

            
            assert (inputFlit[i].getValid() == false);
            continue;
        }

        if (inputFlit[i].getValid()){
            if (inputFlit[i].getDest().x == xDim && inputFlit[i].getDest().y == yDim){
                //Got the flit.
                inputFlit[i].setCompleteTime(cycle);

                if (debugMode){
                    std::cout << "(Router/acceptFlit) :: Router: (" << xDim << "," << yDim  <<" Flit accepted:\n";
                    inputFlit[i].print();
                }
                //---------------------------------------
                // Flit has reached the destination
                History hist;
           
                hist.xSrc = inputFlit[i].getSrc().x;
                hist.ySrc = inputFlit[i].getSrc().y;

                hist.xDest = inputFlit[i].getDest().x;
                hist.yDest = inputFlit[i].getDest().y;

                hist.dir = (Direction)i;
                hist.id = inputFlit[i].getId();
                hist.portType = Destination;
                hist.time = getCycleCount();

                history.push_back(hist);
                //--------------------------------
                coreCompletedFlit.push_back(inputFlit[i]);
                inputFlit[i].resetValid();
                stat.completedFlitCount += 1;
                return;
            }
        }
    }
}

void Router :: routeOldestFlit(){
    //Route oldest flit and put it to output port
    if (validInputFlitCount() == 0){
        return;
    }

    Direction dir = getOldestInputFlit(); 

    if (debugMode){
        std:: cout << " (routeOldestFlit) :: Router: (" << xDim << "," << yDim << "): Oldest input is present in direction: " << convert2Direction(dir) << "\n";
        std :: cout << "Oldest Input flit:\n ";
        inputFlit[dir].print();
    }
    Direction outDir;
    int destX, destY, id;
    
    assert (inputFlit[dir].getValid());

    destX = inputFlit[dir].getDest().x;
    destY = inputFlit[dir].getDest().y;
    id = inputFlit[dir].getId();

    outDir = getOutputPortDirection(destX, destY, id);
    

    if (debugMode){
        std::cout << "(routeOldestFlit) :: Router: (" << xDim << "," << yDim << "): Output port selected: " << convert2Direction(outDir) << "\n";
    }

    outputFlit[outDir] = inputFlit[dir];
    //-------------------------------------
    // Oldest input flit is getting assigned to output
    History hist;
    hist.xSrc = inputFlit[dir].getSrc().x;
    hist.ySrc = inputFlit[dir].getSrc().y;
    hist.xDest = inputFlit[dir].getDest().x;
    hist.yDest = inputFlit[dir].getDest().y;

    hist.id = inputFlit[dir].getId();
    hist.time = getCycleCount();
    hist.portType = Output;
    hist.dir = (Direction)outDir;
    history.push_back(hist);
    //------------------------------------
    if (debugMode){
        std :: cout << "(routeOldestFlit) :: Router: (" << xDim << "," << yDim << "): Output flit (after port assignment):\n";
        outputFlit[outDir].print();
    }
    inputFlit[dir].resetValid();
    
}

void Router :: routeOtherFlit(){
    //Route rest of the flit
    for (int i =0; i < TotalDir; ++i){

        if (IsForbiddenPort(i)){
            assert (inputFlit[i].getValid() == false);
            continue;
        }

        if ( inputFlit[i].getValid()){
            
            if (debugMode){
                std:: cout << "(routeOtherFlit) :: Router: (" << xDim << "," << yDim << "): Input flit direction: " << convert2Direction((Direction)i ) << "\nInputFlit: \n";
                inputFlit[i].print(); 
            }

            for (int j=0; j < TotalDir; ++j){

                if (IsForbiddenPort(j)){
                    continue;
                }

                if (outputFlit[j].getValid() == false){
                    outputFlit[j] = inputFlit[i];

                    if (debugMode){
                        std :: cout << "(routeOtherFlit) :: Router: (" << xDim << "," << yDim << "), output direction: " << convert2Direction((Direction)j) << "\n";

                        std :: cout << "(routeOtherFlit) :: Router: (" << xDim << "," << yDim << "): Output flit: \n";
                        outputFlit[j].print();
                    } 

                    //-----------------------------
                    // Assigning output port to input flit
                    History hist;
                    hist.xSrc = inputFlit[i].getSrc().x;
                    hist.xDest = inputFlit[i].getSrc().y;

                    hist.xDest = inputFlit[i].getDest().x;
                    hist.yDest = inputFlit[i].getDest().y;

                    hist.dir = (Direction) j;
                    hist.portType = Output;
                    hist.id = inputFlit[i].getId();
                    hist.time = getCycleCount();

                    history.push_back(hist);
                    //------------------------------           
                    inputFlit[i].resetValid();
                    break;
                }
            }
        }
    }
}

void Router :: routeFlit(){
    routeOldestFlit();
    routeOtherFlit();
}
/*
  East, : 0
    West,: 1
    North, : 2
    South, : 3
    TotalDir
*/
void Router :: isCornerEdgeRouter(){

    if ( xDim == 0 && yDim == 0){
        // Upper left corner
        //Forbidden port: West, North
        forbiddenPort.insert(1);
        forbiddenPort.insert(2);
        std :: cout << "Router (" << xDim << "," << yDim << ") is at upper left corner.\n";
    }
    
    else if ( xDim == (config.x - 1) && yDim == 0){
        // Upper right corner
        //Forbidden port: East, North
        forbiddenPort.insert(0);
        forbiddenPort.insert(2);
        std :: cout << "Router (" << xDim << "," << yDim << ") is at upper right corner.\n";
    }

    else if ( xDim == 0 && yDim == (config.y - 1)){
        //Lower left corner
        // Forbidden port: West, South
        forbiddenPort.insert(1);
        forbiddenPort.insert(3);
        std :: cout << "Router (" << xDim << "," << yDim << ") is at lower left corner.\n";
    }

    else if ( (xDim == (config.x -1) ) && (yDim == (config.y - 1))){
        // Lower right corner
        //Forbidden port: East, South
        forbiddenPort.insert(0);
        forbiddenPort.insert(3);
        std :: cout << "Router (" << xDim << "," << yDim << ") is at lower right corner.\n";
        
    }

    //Check if the router is located on edge
    else if ( xDim == 0){
        //Left edge
        // Forbidden port: West
        forbiddenPort.insert(1);

        std :: cout << "Router (" << xDim << "," << yDim << ") is at left edge.\n";
    }

    else if (xDim == config.x - 1){
        // Right edge
        // Forbidden port: East
        forbiddenPort.insert(0);
        std :: cout << "Router (" << xDim << "," << yDim << ") is at right edge.\n";
        
    }

    else if (yDim == 0){
        //Upper edge
        // Forbidden port: North
        forbiddenPort.insert(2);
        std :: cout << "Router (" << xDim << "," << yDim << ") is at upper edge.\n";
    }

    else if (yDim == config.y - 1){
        //Lower edge
        //Forbidden port: South
        forbiddenPort.insert(3);
        std :: cout << "Router (" << xDim << "," << yDim << ") is at lower edge.\n";
        
    } else {
        std :: cout << "Router (" << xDim << "," << yDim << ") is not corner or edge router.\n";
    }

    

}
//----------------------------------------------------------
void Router :: printStats(){
    std:: cout << "Router : (" << xDim << " , " << yDim << ")\n";
    std:: cout << "Total injected Flit: " << stat.injectFlitCount << "\n";
    std :: cout << "Total completed flit: " << stat.completedFlitCount << "\n";
    std :: cout << "---------------------------------------------------------\n";
}

void Router :: printCompletedFlit(){

    if (coreCompletedFlit.size() == 0){
        return;
    }

    std :: deque <Flit> :: iterator itr;
    std :: cout << " Completed Flit in router (" << xDim << "," << yDim << ")\n";

    for (itr = coreCompletedFlit.begin(); itr != coreCompletedFlit.end(); ++itr){
        itr->print();
    }
}

bool Router :: IsForbiddenPort(int i){

    if (forbiddenPort.find(i) != forbiddenPort.end()){
        return true; //Found port in forbidden list
    }

    return false;
}

void Router :: printForbiddenList(){

    std :: cout << "Forbidden list size: " << forbiddenPort.size() << "\n";

    if (forbiddenPort.size()){
        std :: set <int> :: iterator itr;

        for (itr = forbiddenPort.begin(); itr != forbiddenPort.end(); ++itr){
            std :: cout << *itr << ", ";
        }
        std :: cout << "\n";
    }
}

void Router :: printHistory(){
    std :: cout << "Router (" << xDim << "," << yDim << ") history:\n";
    for (int i =0; i < history.size(); ++i){
        
        std :: cout << "Source: (" << history[i].xSrc << "," << history[i].ySrc << "), Destination: (" << history[i].xDest << "," << history[i].yDest << ") ";
        std :: cout << " id: " << history[i].id << ", portType: " << convertPortType2String(history[i].portType) << ", direction: " << convert2Direction(history[i].dir) << ", time: " << history[i].time << "\n";

    }
}