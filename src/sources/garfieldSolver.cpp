#include "garfieldSolver.h"
#include <iostream>

void getMeanY(std::vector<Atom> atoms, garfieldSlice *slice) {
    int atomCount = 0;
    slice->meanY = 0;
    std::string userInput;
    //printf("atomX : %f maxx : %f minx : %f \n",atoms[0].x,slice->maxX,slice->minX);
    for (int i = 0; i<atoms.size();i++) {
        Atom atom = atoms[i];

        if (atom.x <= slice->maxX && atom.x >= slice->minX) {
            // std::cout << "YES Atom : " << atom.name << "x : " << atom.x << "minX : " << slice->minX << "maxX" << slice->maxX <<std::endl;
            // std::cout << "Entrez quelque chose : ";
            // std::getline(std::cin, userInput);
            //printf("zzz\n");
            atomCount++;
            slice->meanY+=atom.y;
            //printf("%f\n",slice->meanY);
        }

    }
    // std::cout << "AtomCount :" << atomCount << std::endl;
    // printf("%f",slice->meanY/atomCount);
    slice->meanY = slice->meanY/atomCount;
    //garfieldSlice result;
}

void sortAtoms(std::vector<Atom> atoms, garfieldSlice *slice,std::vector<Atom> *atomsL1,std::vector<Atom> *atomsL2) {
    int supcount = 0,infcount = 0;
    for (int i = 0; i<atoms.size();i++) {
        Atom atom = atoms[i];
        if (atom.x <= slice->maxX && atom.x >= slice->minX) {
            if(atom.y > slice->meanY) {
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
        getMeanY(atoms,&garf.slices[i]);
        std::cout << "Tranche : " << i << " début :" << garf.slices[i].minX << " fin : "<< garf.slices[i].maxX << " moyenne en Y : " << garf.slices[i].meanY << std::endl;
        sortAtoms(atoms,&garf.slices[i],atomsL1,atomsL2);
        
    }
}
