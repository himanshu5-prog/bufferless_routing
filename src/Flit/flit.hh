#ifndef _FLIT_
#define _FLIT_

#include<iostream>
#include <string>
enum Direction {
    East,
    West,
    North,
    South,
    TotalDir
};

inline std::string convert2Direction(Direction dir){
   if (dir == East){
        return "East";
   } else if (dir == West){
        return "West";
   } else if ( dir == North){
        return "North";
   } else if ( dir == South){
        return "South";
   }

   return "Whatever";
}
struct Coord {
    int x;
    int y;
};

class Flit {
    Coord src;
    Coord dest;
    unsigned int id;
    bool valid;
    unsigned int injectTime;
    unsigned int completeTime;

    public:
    //Function related to Src and Dest
    Coord getSrc();
    Coord getDest();
    void setSrc(Coord c);
    void setDest(Coord c);
    //--------------------------------
    //Function related to ID
    unsigned int getId();
    void setId(unsigned int x) { id = x;}
    //-----------------------------------
    //Function related to valid
    bool getValid();
    void setValid();
    void resetValid();
    //----------------------------
    //Functions related to time-------
    void setInjectTime(unsigned int t);
    unsigned int getInjectTime() {return injectTime;}
    void setCompleteTime(unsigned int t);
    unsigned int getCompleteTime() { return completeTime;}
    //---------------------------------
    //Print function-------------------
    void print();
    //-----------------------------------
    //Constructors-----------------------
    Flit();
    Flit(Coord s, Coord d, int i, int t);
    //------------------------------------
};
#endif