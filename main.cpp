#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>


#include "src/headers/fcts.h"
#include "src/headers/groReader.h"
#include "src/headers/garfieldSolver.h"
//#include "src/headers/Atom.h"
#include "src/headers/Algorithm.h"
#include "src/headers/Bilayer.h"
#include "src/headers/Molecule.h"


int main(int argc, char* argv[]) {
    helloWorld();

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <gro_file.gro>" << std::endl;
        return 1;
    }

    std::string groFileName = argv[1];
    std::vector<Atom> atoms = readGroFile(groFileName);

    std::cout << "Atoms length: " << atoms.size() << std::endl;

    // Génère un nombre aléatoire entre 0 (inclus) et atoms.size() (exclus)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, atoms.size() - 1);
    int randomIndex = distribution(gen);

    atoms[randomIndex].show();

    // Utilisez les données lues à partir du fichier .gro dans votre analyse de la structure des membranes lipidiques
    // garfield garf;
    // garf.numSlices = 5;
    // GarfieldLoop(garf,atoms);
    // Utilisez la fonction createMoleculesFromAtoms pour obtenir un vecteur de molécules
    std::vector<Molecule> allMolecules = createMoleculesFromAtoms(atoms);

    // Affichez les noms des molécules
    for (const auto& molecule : allMolecules) {
        std::cout << "Molecule Name: " << molecule.getName() << std::endl;
    }
    
    return 0;
}