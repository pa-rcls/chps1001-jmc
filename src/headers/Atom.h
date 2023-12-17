#ifndef ATOM_H
#define ATOM_H
#include <vector>
#include <string>
#include <iomanip> 
#include <fstream> 

using namespace std;

struct Atom{
    string name;
    string atomType;
    int id;
    float x, y, z;

    void show();

};

void writeAtomPositionsToFile(const std::vector<Atom>& atoms, const std::string& fileName);
#endif
