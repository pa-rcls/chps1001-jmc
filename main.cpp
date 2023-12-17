#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>

#include <set>
#include "src/headers/fcts.h"
#include "src/headers/groReader.h"
#include "src/headers/garfieldSolver.h"
//#include "src/headers/Atom.h"
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
    writeAtomPositionsToFile(atoms,"positionsatoms.txt");
    // Utilisez les données lues à partir du fichier .gro dans votre analyse de la structure des membranes lipidiques
    // garfield garf;
    // garf.numSlices = 5;
    // GarfieldLoop(garf,atoms);
    // Utilisez la fonction createMoleculesFromAtoms pour obtenir un vecteur de molécules
    vector<Molecule> allMolecules;
    // Appelez la fonction avec le vecteur par référence
    createMoleculesFromAtoms(atoms, allMolecules);
    // Affichez les paramètres de quelques molécules
    for (size_t i = 0; i < std::min(allMolecules.size(), static_cast<size_t>(5)); ++i) {
        const Molecule& molecule = allMolecules[i];
        std::cout << "Molecule Name: " << molecule.name << std::endl;
        //std::cout << "Molecule Feuillet: " << molecule.getMoleculeFeuillet() << std::endl;
        std::cout << "Molecule ID: " << molecule.moleculeId << std::endl;
        std::cout << "Molecule Atoms Reference: " << molecule.atomRef.name << " pos x: " << molecule.atomRef.pos.x  << " pos y: " << molecule.atomRef.pos.y  << " pos z: " << molecule.atomRef.pos.z << std::endl;
       // std::cout << "Molecule Orientation: " << molecule.orientation<< std::endl;

        // Affichez le centre de masse de la molécule
        Vector3D temp = molecule.centerOfMass;
        std::cout << "Molecule Center of Mass pos : x " << temp.x << " y : " << temp.y << " z : " << temp.z << std::endl;

        std::cout << "------------------------" << std::endl;
    }




     // Initialisez les compteurs
    int countChol = 0;
    int countDppc = 0;

    // Parcourez le vecteur des molécules
    for (const Molecule& molecule : allMolecules) {
        if (molecule.name.find("DPPC") != std::string::npos) {
            countDppc +=1;
        } else if (molecule.name.find("CHOL") != std::string::npos) {
            countChol +=1;
        }
    }

    // Affichez les résultats
    std::cout << "Nombre total de DPPC : " << countDppc << std::endl;
    std::cout << "Nombre total de CHOL : " << countChol << std::endl;
    // Imprimez le nombre de molécules
    std::cout << "Number of molecules: " << allMolecules.size() << std::endl;
    saveMoleculesToFile(allMolecules, "output.txt");

/*


     // Utilisez un ensemble pour stocker les noms uniques de molécules
    std::set<std::string> moleculeNames;

    // Parcourez le vecteur d'atomes et ajoutez les noms de molécules à l'ensemble
    for (const Atom& atom : atoms) {
        std::istringstream iss(atom.name);
        std::string moleculeName;
        iss >> moleculeName;  // Lire le premier mot du nom de l'atome

        // Ajouter le nom de la molécule à l'ensemble
        moleculeNames.insert(moleculeName);
    }

    // Affichez le nombre de molécules différentes de DPPC et CHOL
    int countDPPC = 0;
    int countCHOL = 0;

    for (const std::string& moleculeName : moleculeNames) {
        if (moleculeName.find("DPPC") != std::string::npos) {
            countDPPC++;
        } else if (moleculeName.find("CHOL") != std::string::npos) {
            countCHOL++;
        }
    }

    // Affichez les résultats
    std::cout << "Nombre de molécules différentes de DPPC : " << countDPPC << std::endl;
    std::cout << "Nombre de molécules différentes de CHOL : " << countCHOL << std::endl;

*/
    return 0;
}