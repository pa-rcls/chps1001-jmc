#ifndef BILAYER_H
#define BILAYER_H

#include <vector>
#include "Molecule.h"

class Bilayer {
public:
    void addMolecule(const Molecule& molecule);
    void addMolecule(const Molecule& molecule, Part part);  // Surcharge avec l'énumération

    void printUpperLeaflet() const;
    void printLowerLeaflet() const;
    enum class Part {
        Upper,
        Lower
    };

private:
    std::vector<Molecule> upperLeaflet;
    std::vector<Molecule> lowerLeaflet;
};

#endif
