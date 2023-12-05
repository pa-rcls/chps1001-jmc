#include "Atom.h"
#include <iostream>

void Atom::show() {
    //Printing all element's informations
    std::cout << "Name: " << name << std::endl;
    std::cout << "Atom Type: " << atomType << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Position (X, Y, Z): " << x << ", " << y << ", " << z << std::endl;
}