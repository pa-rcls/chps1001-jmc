#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Atom.h"
#include "groReader.h"

#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cfloat>

using namespace std;

typedef struct {
	unsigned int n1, n2;
	float distance;
} edge_t;

typedef struct {
	unsigned int n_atoms;	// Nombre de sommets
	vector<Atom> atoms;		// Liste des atomes
	float **matrix;			// Matrice d'adjacence
	
	unsigned int n_edges;	// Nombre d'arêtes du graphe complet
	edge_t *edges;			// Liste des arêtes du graphe complet
	
	edge_t *acpm;			// Liste des arêtes de l'ACPM
	
	vector<Atom> layer1;
	vector<Atom> layer2;
} graph_t;

void init_graph(graph_t *, char *);

void free_graph(graph_t *);

float distance_between(Atom *, Atom *);

int compare_edges(const void *, const void *);

#endif
