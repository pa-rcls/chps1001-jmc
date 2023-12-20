#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

#include "src/headers/groReader.h"
#include "src/headers/garfieldSolver.h"
//#include "src/headers/Atom.h"
#include "src/headers/Molecule.h"
#include "src/headers/graph.h"


int main(int argc, char* argv[]) {
	
	char * groFile;
    std::string groFileName = "none";
	std::string solver = "Graph";
	int numSlices = 5;
	if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " -source=<gro_file.gro> " << " [-solver=[Graph][GF][AM]] " << " [-n_slices=[number_of_slices_for_Garfield_Solver]] "<< std::endl;
        std::cerr << "Default values : " << "-solver=Graph " << "-n_slices=5 " << std::endl;
        return 1;
    }

	for (int i=0;i<argc;i++) {
		std::string argument = argv[i];
		//Check if argument is for gro file
		if (argument.find("-source=") == 0) {
			groFileName = argument.substr(8);
			//char *groFile = argument.substr(8).c_str();
			groFile = new char[argument.substr(8).length() + 1];
			strcpy(groFile, argument.substr(8).c_str());
			std::cout << groFile << std::endl;
			printf("test1\n");
		}
		//Check if argument is for solver
		if (argument.find("-solver=") == 0) {
			solver = argument.substr(8);
			printf("test2\n");

		}
		//Check if argument is for nSlices
		if (argument.find("-n_slices=") == 0) {
			printf("test3\n");
			try {
				numSlices = std::stoi(argument.substr(10));
			} catch (const std::invalid_argument& ia) {
				std::cerr << "Invalid argument: " << ia.what() << std::endl;
			} catch (const std::out_of_range& oor) {
				std::cerr << "Out of range error: " << oor.what() << std::endl;
			}
		}

	}
	std::cout << "Source = " << groFileName << " Solver = " << solver << "nSlices = " << numSlices << std::endl; 


	std::vector<Atom> atoms = readGroFile(groFileName);
	if (groFileName == "none" || atoms.size() == 0) {
		std::cout << "Error while reading gro file. Aborting" << std::endl;
		return 1;
	}
	std::cout << "Number of atoms before solving : " << atoms.size() << std::endl;
	std::vector<Atom> atomsL1;
    std::vector<Atom> atomsL2;


	double tick = clock();

	if (solver == "Graph") {
		//Graph Solver		
		graph_t graph;
		init_graph(&graph, groFileName.c_str());
		
		check_solution(&graph.layer1, &graph.layer2, groFile);
		writeGroFile(groFileName,&graph.layer1,&graph.layer2);
		
		free_graph(&graph);

	} else if (solver == "GS") {

		garfield garf;
		garf.numSlices = numSlices;
		GarfieldLoop(garf,atoms,&atomsL1,&atomsL2);
		std::cout << "Number of atoms in the layers :" << atomsL1.size() + atomsL2.size() << std::endl;
		check_solution(&atomsL1, &atomsL2, groFile);
		writeGroFile(groFileName,&atomsL1,&atomsL2);

	} else if (solver == "AM") {
		solveurmolecule(atoms);
	} else {
		std::cout << solver <<  " : solver unreconized. Aborting" << std::endl;
	}


	double tock = clock();
	std::cout << "Time in Solver : " << (tock-tick)/CLOCKS_PER_SEC << "s" << std::endl;

    return 0;
}