#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

#include <set>
#include "src/headers/fcts.h"
#include "src/headers/groReader.h"
#include "src/headers/garfieldSolver.h"
//#include "src/headers/Atom.h"
#include "src/headers/Molecule.h"
#include "src/headers/graph.h"


int main(int argc, char* argv[]) {
    // helloWorld();

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <gro_file.gro>" << std::endl;
        return 1;
    }

    // std::string groFileName = argv[1]; // Récupère le nom du fichier .gro à partir des arguments de la ligne de commande
    // std::vector<Atom> atoms = readGroFile(groFileName);

    
    // std::cout << "Atoms length: " << atoms.size() << std::endl;
   
  // Génère un nombre aléatoire entre 0 (inclus) et atoms.size() (exclus)
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<int> distribution(0, atoms.size() - 1);
    // int randomIndex = distribution(gen);

    // atoms[randomIndex].show();
    // Utilisez les données lues à partir du fichier .gro dans votre analyse de la structure des membranes lipidiques
	// double tick = clock();
    // garfield garf;
    // garf.numSlices = 5;
    // GarfieldLoop(garf,atoms);
	// double tock = clock();
	// cout << "Garfield : " << (tock-tick)/CLOCKS_PER_SEC << endl;
	solveurmolecule(atoms);
	double tick = clock();
	
	graph_t graph;
	init_graph(&graph, argv[1]);
	
	check_solution(&graph.layer1, &graph.layer2, argv[1]);
	
	free_graph(&graph);
	
	double tock = clock();
	cout << (tock-tick)/CLOCKS_PER_SEC << "s" << endl;
  
  return 0;
}