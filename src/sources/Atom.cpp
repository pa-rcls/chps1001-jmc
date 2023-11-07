#include "Atom.h"
#include <iostream>

void Atom::show() {
    // Utilisez la fonction std::cout pour afficher les informations de l'atome
    std::cout << "Name: " << name << std::endl;
    std::cout << "Atom Type: " << atomType << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Position (X, Y, Z): " << x << ", " << y << ", " << z << std::endl;
    std::cout << "Extra1: " << extra1 << std::endl;
    std::cout << "Extra2: " << extra2 << std::endl;
    std::cout << "Extra3: " << extra3 << std::endl;
}