#ifndef MOLECULE_H
#define MOLECULE_H

#include <vector>
#include <string>
#include "Atom.h"
#include "calcul.h"


struct Molecule {
    std::string name;
    std::string moleculeType;
    int moleculeId;
    std::vector<Atom> atoms;
    std::string getName() const;
    Vector3D centerOfMass; 
};

std::vector<Molecule> createMoleculesFromAtoms(const std::vector<Atom>& atoms);


#endif
