#ifndef GROVREADER_H
#define GROVREADER_H

#include <string>
#include <vector>
#include "Atom.h"

std::vector<Atom> readGroFile(const std::string& filename);

#endif