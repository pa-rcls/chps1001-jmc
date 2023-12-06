#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include "Atom.h"
#include "Molecule.h"
#include "Bilayer.h"

float calculateMedian(const std::vector<Atom>& atoms, char dimension);

void processMolecules(Bilayer& bilayer, const std::vector<Molecule>& allMolecules,
                      const std::vector<Atom>& allAtoms);

#endif
