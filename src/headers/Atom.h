#ifndef ATOM_H
#define ATOM_H

#include <string>

struct Atom {
    std::string name;
    std::string atomType;
    int id;
    double x, y, z;
    double extra1, extra2, extra3;

    void show();
};


#endif
