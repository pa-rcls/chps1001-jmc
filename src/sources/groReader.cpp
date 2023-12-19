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
    std::cout << frame << std::endl;
    std::cout << filename;
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