#ifndef MOLECULE_H
#define MOLECULE_H

#include <vector>
#include <string>
#include "Atom.h"

struct Molecule {
    std::string name;
    std::string moleculeType;
    int moleculeId;
    std::vector<Atom> atoms;
};

#endif
