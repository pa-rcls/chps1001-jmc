#include "garfieldSolver.h"
#include <iostream>

//Getting the mean in Z dimension for all slices
void getmeanZ(std::vector<Atom> atoms, garfieldSlice *slice) {
    int atomCount = 0;
    slice->meanZ = 0;
    std::string userInput;
    for (int i = 0; i<atoms.size();i++) {
        Atom atom = atoms[i];

        if (atom.x <= slice->maxX && atom.x >= slice->minX) {
            atomCount++;
            slice->meanZ+=atom.z;
        }

    }
    slice->meanZ = slice->meanZ/atomCount;
}

//Sorting atoms between the two layers
void sortAtoms(std::vector<Atom> atoms, garfieldSlice *slice,std::vector<Atom> *atomsL1,std::vector<Atom> *atomsL2) {
    int supcount = 0,infcount = 0;
    for (int i = 0; i<atoms.size();i++) {
        Atom atom = atoms[i];
        if (atom.x <= slice->maxX && atom.x >= slice->minX) {
            if(atom.z > slice->meanZ) {
                supcount+=1;
                //std::cout << "Name : " << atom.name << " Layer sup" << std::endl;
                atomsL1->push_back(atom);
            } else {
                infcount+=1;
                //std::cout << "Name : " << atom.name << " Layer inf" << std::endl;
                atomsL2->push_back(atom);
            }
                
        }
    }
    printf("feuillet sup : %d, feuillet inf : %d\n",supcount,infcount);
}

//Solver's main loop
void GarfieldLoop(garfield garf,std::vector<Atom> atoms,std::vector<Atom> *atomsL1,std::vector<Atom> *atomsL2) {

    garf.slices.resize(garf.numSlices);

    // Parcours des atomes pour trouver le maximum
    float maxX = atoms[0].x;
    float minX = atoms[0].x;
    for (const auto& atom : atoms) {
        if (atom.x > maxX) {
            maxX = atom.x;
        }
        if (atom.x < minX) {
            minX = atom.x;
        }
    }
    garf.sliceWidth = (maxX-minX)/garf.numSlices;
    std::cout << "maxX :" << maxX << std::endl;
    std::cout << "minX :" << minX << std::endl;
    std::cout << "Nombre de tranches : " << garf.numSlices << std::endl;
    std::cout << "Epaisseur de tranches : " << garf.sliceWidth << std::endl;
    // Boucle sur les tranches
    for (int i = 0;i<garf.numSlices;i++) {
        printf("\n\n");
        garf.slices[i].maxX = ((i+1)*garf.sliceWidth)-abs(minX);
        garf.slices[i].minX = (i*garf.sliceWidth)-abs(minX);
        getmeanZ(atoms,&garf.slices[i]);
        std::cout << "Tranche : " << i << " début :" << garf.slices[i].minX << " fin : "<< garf.slices[i].maxX << " moyenne en X : " << garf.slices[i].meanZ << std::endl;
        sortAtoms(atoms,&garf.slices[i],atomsL1,atomsL2);
        
    }
}
