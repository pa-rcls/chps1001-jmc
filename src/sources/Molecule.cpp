// Molecule.cpp

#include "Molecule.h"
#include "calcul.h"
std::string Molecule::getName() const {
    // Implémentez le code pour obtenir le nom de la molécule
    // Par exemple, vous pouvez retourner le nom de la première atom de la molécule.
    if (!atoms.empty()) {
        return name;
    } else {
        return "Unknown";
    }
}

std::vector<Molecule> createMoleculesFromAtoms(const std::vector<Atom>& atoms) {
    std::vector<Molecule> molecules;

    for (const auto& atom : atoms) {
        bool moleculeExists = false;

        // Vérifie si la molécule existe déjà dans le vecteur de molécules
        for (auto& molecule : molecules) {
            if (molecule.name == atom.name) {
                molecule.atoms.push_back(atom);
                moleculeExists = true;
                break;
            }
        }

        // Si la molécule n'existe pas encore, la crée
        if (!moleculeExists) {
            Molecule newMolecule;
            newMolecule.name = atom.name;
            newMolecule.moleculeType = "default"; // Vous pouvez le changer si nécessaire
            newMolecule.moleculeId = std::stoi(atom.name.substr(0, atom.name.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ")));
            newMolecule.atoms.push_back(atom);

            molecules.push_back(newMolecule);
        }

        
    }

     // Calculer le centre de masse pour chaque molécule
    for (auto& molecule : molecules) {
        molecule.centerOfMass = calculateCenterOfMass(molecule.atoms);
    }

    return molecules;
}