#include <iostream>
#include <vector>
#include <random>

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

    // Déclaration des variables pour les molécules et les atomes
    std::vector<Molecule> allMolecules;
    // Initialisez allMolecules en lisant les données à partir du fichier ou d'une autre source

    std::vector<Atom> allAtoms = readGroFile(groFileName);

    // Création d'une instance de Bilayer
    Bilayer bilayer;

    // Appel de la fonction d'algorithme
    processMolecules(bilayer, allMolecules, allAtoms);

    // Affichage des molécules dans les parties Upper et Lower de la bilaye
    std::cout << "Upper Leaflet:" << std::endl;
    bilayer.printUpperLeaflet();

    std::cout << "\nLower Leaflet:" << std::endl;
    bilayer.printLowerLeaflet();

    // Écriture des positions des atomes dans un fichier
    writeAtomPositionsToFile(atoms, "positionatoms.txt");

    return 0;
}