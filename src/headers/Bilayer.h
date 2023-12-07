// Bilayer.h

#ifndef BILAYER_H
#define BILAYER_H

#include "Molecule.h"  // Assurez-vous d'inclure le fichier qui définit la classe Molecule
#include <vector>
#include <iostream>

class Bilayer {
public:
    enum class Part { Upper, Lower };

    void addMolecule(const Molecule& molecule);
    void addMolecule(const Molecule& molecule, Part part);

    void printAllMolecules() const;
    void printUpperLeaflet() const;
    void printLowerLeaflet() const;

    void saveToFile(const std::string& fileName, const std::vector<Molecule>& molecules) const;
    void saveUpperLeafletToFile(const std::string& fileName) const;
    void saveLowerLeafletToFile(const std::string& fileName) const;

private:
    std::vector<Molecule> allMolecules;
    std::vector<Molecule> upperLeaflet;
    std::vector<Molecule> lowerLeaflet;
};

#endif  // BILAYER_H
