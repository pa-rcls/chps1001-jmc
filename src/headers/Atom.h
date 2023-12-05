#ifndef ATOM_H
#define ATOM_H

#include <string>

using namespace std;

struct Atom {
    string name;
    string atomType;
    int id;
    float x, y, z;

    void show();
};


#endif
