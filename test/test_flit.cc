#include <iostream>
#include "../src/Flit/flit.hh"

int main(){
    Flit a;
    Coord c,d;
    c.x = 1;
    c.y = 2;
    
    d.x = 2;
    d.y = 1;

    Flit fl(c,d,1,12);

    std:: cout << "Flit a information:\n";
    a.print();
 
    std :: cout << "Flit b information\n";
    fl.print();


    return 0;
}