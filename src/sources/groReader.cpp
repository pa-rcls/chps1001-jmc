#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "groReader.h"

vector<Atom> readGroFile(const string& filename) {
    vector<Atom> atoms;

    ifstream file(filename);
    if (!file.is_open()) { // Open file
        cerr << "Unable to open the file: " << filename << endl;
        return atoms;
    }

    string line;
    int atomCount;
    getline(file, line);  // Ignore first line
    if (!(file >> atomCount)) {
        cerr << "Invalid file format." << endl;
        return atoms;
    }
    getline(file, line);  // Consume rest of the line

    atoms.reserve(atomCount);

    while (getline(file, line)) { //Read line and create new element
        Atom atom;
        file >> atom.name >> atom.atomType >> atom.id >> atom.x >> atom.y >> atom.z;
        if (atom.name.find("DPPC") != std::string::npos || 
            atom.name.find("CHOL") != std::string::npos || 
            atom.name.find("POPC") != std::string::npos) {
            atoms.push_back(atom);
        }
    }

    file.close(); //don't forget to close file !
    return atoms;
}


void check_solution(vector<Atom> *layer1, vector<Atom> *layer2, char *path) {
	vector<int> leaflet1 = vector<int>();
	vector<int> leaflet2 = vector<int>();
	
	// Récupération du chemin vers le fichier leaflets.txt
	char leaflet_path[256];
	memcpy(leaflet_path, path, strrchr(path, '/') - path + 1 );
	strcat(leaflet_path, "leaflets.txt");
	
	filebuf fb;
	fb.open(leaflet_path, ios::in);
	
	char str[256];
	
	istream in(&fb);
	
	// On ignore la première ligne
	in.getline(str, 256);
	char *tmp;
	
	// Lecture de la première couche
	in.getline(str, 256);
	while(str[0] != '[') {
		
		tmp = strtok(str, " ");
		while(tmp != NULL) {
			leaflet1.push_back(atoi(tmp));
			tmp = strtok(NULL, " ");
		}
		
		in.getline(str, 256);
	}
	
	// Lecture de la seconde couche
	in.getline(str, 256);
	while(!in.eof()) {
		
		tmp = strtok(str, " ");
		while(tmp != NULL) {
			leaflet2.push_back(atoi(tmp));
			tmp = strtok(NULL, " ");
		}
		
		in.getline(str, 256);
	}
	
	fb.close();
	
	// Comparaison des deux couches avec le fichier leaflet
	if( ( compare_vector(layer1, &leaflet1) || compare_vector(layer1, &leaflet2) )
	 && ( compare_vector(layer2, &leaflet1) || compare_vector(layer2, &leaflet2) ) ) {
		printf("La solution obtenue correspond à la solution de référence\n");
	}
	else {
		printf("La solution obtenue ne correspond pas à la solution de référence\n");
	}
}


int compare_vector(vector<Atom> *layer, vector<int> *leaflet) {
	for(int i=0; i < leaflet->size(); ++i) {
		int found = 0;
		for(int j=0; j<layer->size() && !found; ++j) {
			if( (*leaflet)[i] == atoi( (*layer)[j].name.substr(0, (*layer)[i].name.size() - 4).c_str() )) {
				found = 1;
			}
		}
		if(!found) {
			return 0;
		}
	}
	return 1;
}