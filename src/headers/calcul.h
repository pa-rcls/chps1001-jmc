#ifndef CALCUL_H
#define CALCUL_H

#include <vector>
#include "Atom.h"  
struct Vector3D {
    float x, y, z;
};

Vector3D calculateCenterOfMass(const std::vector<Atom>& atoms);

#endif
