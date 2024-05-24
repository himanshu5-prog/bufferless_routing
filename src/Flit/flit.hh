#ifndef _FLIT_
#define _FLIT_

#include<iostream>

enum Direction {
    East,
    West,
    North,
    South,
    TotalDir
};

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