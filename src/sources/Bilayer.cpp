#include "Bilayer.h"

void Bilayer::addMolecule(const Molecule& molecule) {
    // Ajouter la molécule à la classe Bilayer (logique par défaut, vous pouvez personnaliser)
    allMolecules.push_back(molecule);
}

void Bilayer::addMolecule(const Molecule& molecule, Part part) {
    // Ajouter la molécule à la partie spécifiée de la classe Bilayer (logique par défaut, vous pouvez personnaliser)
    if (part == Part::Upper) {
        upperLeaflet.push_back(molecule);
    } else if (part == Part::Lower) {
        lowerLeaflet.push_back(molecule);
    }
}

void Bilayer::printUpperLeaflet() const {
    for (const auto& molecule : upperLeaflet) {
        std::cout << "Upper Leaflet - Molecule: " << molecule.name << ", Type: " << molecule.moleculeType << ", ID: " << molecule.moleculeId << std::endl;
    }
}

void Bilayer::printLowerLeaflet() const {
    for (const auto& molecule : lowerLeaflet) {
        std::cout << "Lower Leaflet - Molecule: " << molecule.name << ", Type: " << molecule.moleculeType << ", ID: " << molecule.moleculeId << std::endl;
    }
}