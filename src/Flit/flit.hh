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

    Coord getSrc();
    Coord getDest();
    unsigned int getId();
    void setId(unsigned int x) { id = x;}
    void setSrc(Coord c);
    void setDest(Coord c);
    bool getValid();
    void setValid();
    void resetValid();
    void setInjectTime(unsigned int t);
    void setCompleteTime(unsigned int t);
    void print();
    
    //Constructor
    Flit();
    Flit(Coord s, Coord d, int i, int t);
};
#endif