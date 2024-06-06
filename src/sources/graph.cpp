#include "graph.h"


void init_graph(graph_t *graph,const char *path) {
	// Variables locales
	unsigned int i, j, index;
	std::cout << path << std::endl;
	// Récupération de l'ensemble des atomes du fichier
	vector<Atom> temp = readGroFile(path);
	cout << "Nombre d'atomes dans le fichier : " << temp.size() << endl;
	
	
	// Récupération de l'ensemble des atomes de références des lipides
	for(i=0; i<temp.size(); ++i) {
		if( temp[i].name.find("DPPC") != string::npos && temp[i].atomType.find("N") != string::npos ) {
			graph->atoms.push_back(temp[i]);
		}
		else if( temp[i].name.find("CHOL") != string::npos && temp[i].atomType.find("ROH") != string::npos ) {
			graph->atoms.push_back(temp[i]);
		}
		else if( temp[i].name.find("POPC") != string::npos && temp[i].atomType.find("N") != string::npos ) {
			graph->atoms.push_back(temp[i]);
		}
	}
	graph->n_atoms = graph->atoms.size();
	cout << "Nombre d'atomes dans le graphe : " << graph->n_atoms << endl;
	
	
	// Allocation de la matrice d'adjacence
	graph->matrix = (float**) malloc( sizeof(float*) * graph->n_atoms );
	for(i=0; i<graph->n_atoms; ++i) {
		graph->matrix[i] = (float*) malloc( sizeof(float) * graph->n_atoms );
		memset(graph->matrix[i], 0, sizeof(float) * graph->n_atoms );
	}
	cout << "Taille de la matrice d'adjacence : " << pow(graph->n_atoms, 2) << endl;
	
	
	// Allocation de la liste des arêtes du graphe complet
	graph->n_edges = graph->n_atoms * (graph->n_atoms - 1) * 0.5f,
	graph->edges = (edge_t*) malloc( sizeof(edge_t) * graph->n_edges );
	cout << "Nombre d'arêtes théorique du graphe complet : " << graph->n_edges << endl;
	
	
	// Remplissage de la matrice d'adjacence et de la liste des arêtes
	for(i=0, index=0; i<graph->n_atoms; ++i) {
		for(j=i+1; j<graph->n_atoms; ++j) {
			graph->matrix[i][j] = graph->matrix[j][i] = distance_between(&graph->atoms[i], &graph->atoms[j]);
			graph->edges[index++] = { i, j, distance_between(&graph->atoms[i], &graph->atoms[j]) };
		}
	}
	qsort(graph->edges, graph->n_edges, sizeof(edge_t), compare_edges);
	cout << "Nombre d'arêtes pratique du graphe complet : " << index << endl;
	
	
	// cout << endl;
	// for(i=0; i<graph->n_edges; ++i) {
		// cout << graph->edges[i].n1 << "\t" << graph->edges[i].n2 << "\t" << graph->edges[i].distance << endl;
	// }
	// cout << endl;
	
	
	// Calcul du graphe de poids minimal par algorithme de Kruskal
	graph->acpm = (edge_t*) malloc( sizeof(edge_t) * (graph->n_atoms - 1) );
	cout << "Nombre d'arêtes théorique dans l'ACPM: " << graph->n_atoms - 1 << endl;
	
	unsigned int cc[graph->n_atoms];
	for(i=0; i<graph->n_atoms; ++i) {
		cc[i] = i;
	}
	
	unsigned int icc;
	for(i=0, index=0; i<graph->n_edges && index<graph->n_atoms-2; ++i) {
		
		unsigned int s1 = graph->edges[i].n1;
		unsigned int s2 = graph->edges[i].n2;
		
		// Si les deux sommets ne sont pas dans la même composante connexe
		if( cc[s1] != cc[s2] ) {
			// Ajout de l'arête à l'ACPM
			graph->acpm[index++] = graph->edges[i];
			// On fusionne les deux composantes connexes
			icc = cc[s2];
			for(j=0; j<graph->n_atoms; ++j) {
				if( cc[j] == icc ) {
					cc[j] = cc[s1];
				}
			}
		}
	}
	
	cout << "Nombre d'arêtes pratique dans l'ACPM: " << index << endl;
	
	// for(i=0; i<graph->n_atoms; ++i) {
		// cout << cc[i] << endl;
	// }
	
	// Affichage de l'ACPM
	// for(i=0; i<graph->n_atoms-1; ++i) {
		// cout << graph->acpm[i].n1 << "\t" << graph->acpm[i].n2 << "\t" << graph->acpm[i].distance << endl;
	// }
	
	// Remplissage des deux couches
	graph->layer1 = vector<Atom>();
	graph->layer2 = vector<Atom>();
	int layer_id = cc[0];
	
	for(i=0; i<graph->n_atoms; ++i) {
		if(cc[i] == layer_id) {
			graph->layer1.push_back(graph->atoms[i]);
		}
		else {
			graph->layer2.push_back(graph->atoms[i]);
		}
	}
	
	
	// Affichage de la première couche
	for(i=0; i<graph->layer1.size(); ++i) {
		cout << graph->layer1[i].name.substr(0, graph->layer1[i].name.size() - 4) << " ";
	}
	cout << "\n" << endl;
	
	
	// Affichage de la seconde couche
	for(i=0; i<graph->layer2.size(); ++i) {
		cout << graph->layer2[i].name.substr(0, graph->layer2[i].name.size() - 4) << " ";
	}
	cout << "\n" << endl;
}


void free_graph(graph_t *graph) {
	// Free ACPM
	free(graph->acpm);
	graph->acpm = NULL;
	
	// Free sorted list of edges
	free(graph->edges);
	graph->edges = NULL;
	graph->n_edges = 0;
	
	// Free graph matrix
	for(unsigned int i=0; i<graph->n_atoms; ++i) {
		free(graph->matrix[i]);
		graph->matrix[i] = NULL;
	}
	free(graph->matrix);
	graph->matrix = NULL;
	
	// Free graph atom list
	graph->atoms.clear();
	graph->n_atoms = 0;
	
	graph->layer1.clear();
	graph->layer2.clear();
}


float distance_between(Atom *a1, Atom *a2) {
	return sqrt( pow(a2->x - a1->x, 2) + pow(a2->y - a1->y, 2) + pow(a2->z - a1->z, 2) );
}


int compare_edges(const void *edge1, const void *edge2) {
	edge_t *p1 = (edge_t*) edge1;
	edge_t *p2 = (edge_t*) edge2;
	if( p1->distance < p2->distance ) {
		return -1;
	}
	else if( p1->distance > p2->distance ) {
		return 1;
	}
	else {
		return 0;
	}
}
