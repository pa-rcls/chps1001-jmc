#ifndef GARFIELDSOLVER_H
#define GARFIELDSOLVER_H

#include "Atom.h"
#include <vector>

struct garfieldSlice {
    float meanZ = 0; 
    float maxX;
    float minX;
};
struct garfield {
    std::vector<garfieldSlice> slices;
    int numSlices;
    float sliceWidth;
};


//Sorting atoms between the two layers
void sortAtoms(std::vector<Atom> atoms, garfieldSlice *slice,std::vector<Atom> *atomsL1,std::vector<Atom> *atomsL2);

//Getting the mean in Z dimension for all slices
void getMeanZ(const std::vector<Atom> *atoms, garfieldSlice *slice);

//Solver's main loop
void GarfieldLoop(garfield GSData,std::vector<Atom> atoms,std::vector<Atom> *atomsL1,std::vector<Atom> *atomsL2);




#endif