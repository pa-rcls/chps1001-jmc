#ifndef GROVREADER_H
#define GROVREADER_H

#include <string>
#include <vector>
#include "Atom.h"

using namespace std;

vector<Atom> readGroFile(const string& filename); //Read .gro file and creating vector of atom

#endif