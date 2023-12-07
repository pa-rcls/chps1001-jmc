// Bilayer.cpp

#include "Bilayer.h"

void Bilayer::addMolecule(const Molecule& molecule) {
    allMolecules.push_back(molecule);
}

void Bilayer::addMolecule(const Molecule& molecule, Part part) {
    if (part == Part::Upper) {
        upperLeaflet.push_back(molecule);
    } else if (part == Part::Lower) {
        lowerLeaflet.push_back(molecule);
    }
}

void Bilayer::printUpperLeaflet() const {
    std::cout << "Upper Leaflet Molecules:" << std::endl;
    for (const auto& molecule : upperLeaflet) {
        std::cout << molecule.getName() << std::endl;
    }
}

void Bilayer::printLowerLeaflet() const {
    std::cout << "Lower Leaflet Molecules:" << std::endl;
    for (const auto& molecule : lowerLeaflet) {
        std::cout << molecule.getName() << std::endl;
    }
}


void Bilayer::saveToFile(const std::string& fileName, const std::vector<Molecule>& molecules) const {
    std::ofstream outFile(fileName);

    if (!outFile.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier " << fileName << std::endl;
        return;
    }

    for (const auto& molecule : molecules) {
        for (const auto& atom : molecule.atoms) {
            outFile << atom.x << " " << atom.y << " " << atom.z << "\n";
        }
    }

    outFile.close();
}

void Bilayer::saveUpperLeafletToFile(const std::string& fileName) const {
    saveToFile(fileName, upperLeaflet);
}

void Bilayer::saveLowerLeafletToFile(const std::string& fileName) const {
    saveToFile(fileName, lowerLeaflet);
}