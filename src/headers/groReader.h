#ifndef GROVREADER_H
#define GROVREADER_H

#include <string>
#include <vector>
#include <fstream>
#include <istream>
#include <cstring>
#include "Atom.h"

using namespace std;

vector<Atom> readGroFile(const string& filename); //Read .gro file and creating vector of atom

void check_solution(vector<Atom> *, vector<Atom> *, char *);

int compare_vector(vector<Atom> *, vector<int> *);

#endif