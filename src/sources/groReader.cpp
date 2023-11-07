#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Atom {
    std::string name;
    std::string atomType;
    int id;
    double x, y, z;
    double extra1, extra2, extra3;
};

std::vector<Atom> readGroFile(const std::string& filename) {
    std::vector<Atom> atoms;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return atoms;
    }

    std::string line;
    int atomCount;
    getline(file, line);  // Ignore the first line
    if (!(file >> atomCount)) {
        std::cerr << "Invalid file format." << std::endl;
        return atoms;
    }
    getline(file, line);  // Consume the rest of the line

    atoms.reserve(atomCount);

    while (getline(file, line)) {
        Atom atom;
        file >> atom.name >> atom.atomType >> atom.id >> atom.x >> atom.y >> atom.z
            >> atom.extra1 >> atom.extra2 >> atom.extra3;
        atoms.push_back(atom);
    }

    file.close();
    return atoms;
}