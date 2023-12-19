#include "Atom.h"
#include <iostream>

void Atom::show() {
    //Printing all element's informations
    std::cout << "Name: " << name << std::endl;
    std::cout << "Atom Type: " << atomType << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Position (X, Y, Z): " << x << ", " << y << ", " << z << std::endl;
}


void writeAtomPositionsToFile(const std::vector<Atom>& atoms, const std::string& fileName) {
    std::ofstream outFile(fileName.c_str());  // Utilisez .c_str() pour convertir un std::string en const char*
    if (!outFile.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << fileName << std::endl;
        return;
    }

    for (const Atom& atom : atoms) {
        outFile << std::fixed << std::setprecision(3);
        outFile << atom.name << " " << atom.atomType << " " << atom.id << " " << atom.x << " " << atom.y << " " << atom.z << std::endl;
    }

    outFile.close();
}