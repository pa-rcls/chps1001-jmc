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