#include "flit.hh"

// Constructor--------------
Flit :: Flit (){
    src.x = 0;
    src.y = 0;
    dest.x = 0;
    dest.y = 0;
    id = 0;
    valid = false;
    injectTime = 0;
    completeTime = 0;
}

Flit :: Flit (Coord s, Coord d, int i, int t){
    src = s;
    dest = d;
    id = i;
    valid = true;
    injectTime = t;
}
//-------------------------------
// Function related to Src and Dest
Coord Flit :: getDest(){
    return dest;
}

Coord Flit :: getSrc(){
    return src;
}

void Flit :: setSrc(Coord c){
    src = c;
}

void Flit :: setDest(Coord c){
    dest = c;
}

unsigned int Flit :: getId(){
    return id;
}
//--------------------------------
//Function related to time----------------
void Flit :: setInjectTime (unsigned int t){
    injectTime = t;
}

void Flit :: setCompleteTime (unsigned int t){
    completeTime = t;
}
//----------------------------------------
// Functios for Valid-----------
void Flit :: setValid(){
    valid = true;
}

void Flit :: resetValid(){
    valid = false;
}

bool Flit :: getValid(){
    return valid;
}
//----------------------------------
//Print function---------------------------------------------------------------------
void Flit :: print(){
   std :: cout << "####################################\n";
   std :: cout << "Flit Information:\n";
   std :: cout << "source coordinate: (" << src.x << " , " << src.y << ")\n";
   std :: cout << "destination coordinate: (" << dest.x << " , " << dest.y << ")\n";
   std :: cout << "id: " << id << "\n";
   std :: cout << "valid: " << valid << "\n";
   std :: cout << "injection time: " << injectTime << "\n";
   std :: cout << "completion time: " << completeTime << "\n";
   std :: cout << "####################################\n"; 
}
//-----------------------------------------------------------------------------------