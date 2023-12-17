#ifndef MOLECULE_H
#define MOLECULE_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Atom.h"

struct Vector3D {
    float x, y, z;
};
struct AtomReference{
    std::string name;
    Vector3D pos;
};
struct Molecule {

    std::string name;            // nom identification 
    std::string moleculeFeuillet; // feuillet auquel il appartient
    int moleculeId;               // numéro 
    std::vector<Atom> atoms;      // liste atoms
    AtomReference atomRef;   // atom de ref
    int orientation;              // 0 ou 1 pour dire bas ou haut
    Vector3D centerOfMass;        // centre de masse
};

void createMoleculesFromAtoms(const std::vector<Atom>& atoms, std::vector<Molecule>& molecules);
Vector3D calculateCenterOfMass(const std::vector<Atom>& atoms);
int calculateOrientation();
AtomReference determinateReferenceAtom(Molecule molecule);
// Fonction pour sauvegarder les molécules dans un fichier
void saveMoleculesToFile(const std::vector<Molecule>& molecules, const std::string& filename);
#endif // MOLECULE_H
