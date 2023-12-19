#ifndef GARFIELDSOLVER_H
#define GARFIELDSOLVER_H

#include "Atom.h"
#include <vector>

struct garfieldSlice {
    float meanY = 0;
    float maxX;
    float minX;
};
struct garfield {
    std::vector<garfieldSlice> slices;
    int numSlices;
    float sliceWidth;
};

void sortAtoms(std::vector<Atom> atoms, garfieldSlice *slice,std::vector<Atom> *atomsL1,std::vector<Atom> *atomsL2);
void getMeanY(const std::vector<Atom> *atoms, garfieldSlice *slice);
void GarfieldLoop(garfield GSData,std::vector<Atom> atoms,std::vector<Atom> *atomsL1,std::vector<Atom> *atomsL2);




#endif