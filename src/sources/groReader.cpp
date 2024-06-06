#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "groReader.h"

string frame;

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
    frame = line;
    //std::cout << line << std::endl;
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
            atom.name.find("DUPC") != std::string::npos ||
            atom.name.find("CHOL") != std::string::npos || 
            atom.name.find("POPC") != std::string::npos ||
            atom.name.find("DUPC") != std::string::npos) {
                // if (atoms.size() == 0) {
                //     atoms.push_back(atom);
                // } else if(atom.name != atoms.back().name) {
                //     //printf("%s %s\n",atom.name,atoms.back().name);
                //     //std::cout << atom.name << "  " << atoms.back().name << std::endl;
                //     atoms.push_back(atom);
                // }
                atoms.push_back(atom);
            
        }
    }

    file.close(); //don't forget to close file !
    return atoms;
}

void writeGroFile(const string& filename,const vector<Atom> * atomsL1,const vector<Atom> * atomsL2) {
    //std::cout << frame << std::endl;
    //std::cout << filename;
    std::ofstream file("results/"+filename,std::ofstream::out);
    
    if (file.is_open()) { // Vérifie si le fichier est ouvert avec succès
        //file << frame << std::endl;
        //file << atomsL1->size()+atomsL2->size() << std::endl;

        for (int i=0;i<atomsL1->size();i++) {

            Atom atom = (*atomsL1)[i];

            file << atom.name << " " << atom.atomType << " " << atom.id << " " << atom.x << " " << atom.y << " " << atom.z << " " << 0 <<std::endl;

        }
        for (int i=0;i<atomsL2->size();i++) {

            Atom atom = (*atomsL2)[i];

            file << atom.name << " " << atom.atomType << " " << atom.id << " " << atom.x << " " << atom.y << " " << atom.z << " " << 1 <<std::endl;

        }
        file.close(); // Ferme le fichier
        std::cout << "Écriture dans le fichier terminée." << std::endl;
    } else {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }

}

void check_solution(vector<Atom> *layer1, vector<Atom> *layer2, char *path) {
    vector<int> leaflet1 = vector<int>();
    vector<int> leaflet2 = vector<int>();

    // Récupération du chemin vers le fichier leaflets.txt
    char leaflet_path[256];
    memcpy(leaflet_path, path, strrchr(path, '/') - path );
    //cout<<leaflet_path<<endl;
    char* lastSlash = strrchr(path, '/');
    size_t length = lastSlash - path;
    leaflet_path[length] = '\0';
    strcat(leaflet_path, "/leaflets.txt");
    //cout<<leaflet_path<<endl;

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